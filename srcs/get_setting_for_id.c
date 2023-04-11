/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:36:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 18:39:13 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// XYZ : 0.0, 0.0, 0.0
// RGB : 255, 0, 255
// image_path : image_path, bumpmap_path


// C   XYZ   orientation_vec[-1,1]   FOV[0,180]
int get_setting_for_camera(const char *line, t_camera *camera)
{
	size_t		idx;

	idx = 0;
	if (parsing_vec(line, &camera->pos, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &camera->dir, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &camera->fov_deg, &idx) == FAILURE)
		return (FAILURE);

	if (!is_vec_in_normal_range(camera->dir))
		return (FAILURE);

	if (camera->fov_deg < 0.0f || 180.0f < camera->fov_deg)
		return (FAILURE);

	if (line[idx])
		return (FAILURE);

	return (SUCCESS);
}

// A   lightning_ratio[0,1]   RGB[0,255]
int	get_setting_for_ambient(const char *line, t_scene *scene)
{
	size_t		idx;
	float		lightning_ratio;
	t_colorf	color;

	idx = 0;
	if (parsing_double_num(line, &lightning_ratio, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);

	if (lightning_ratio < 0.0f || 1.0f < lightning_ratio)
		return (FAILURE);

	if (!is_color_in_range(color))
		return (FAILURE);

	if (line[idx])
		return (FAILURE);

	scene->ambient_illuminance = get_color_k1c1(lightning_ratio, color);

	return (SUCCESS);
}

t_light_type	get_light_type(t_identifier id)
{
	if (id == id_point_light)
		return (LT_POINT);
	return (LT_SPOT);
}


// L   XYZ   brightness_ratio[0,1]   RGB[0,255]
// sl  XYZ   brightness_ratio[0,1]   RGB[0,255]   angle[0,180]
int get_setting_for_lights(const char *line, t_scene *scene, t_identifier id)
{
	t_light		light;
	size_t		idx;
	t_list		*new_list;
	float		brightness_ratio;
	t_colorf	color;

	light.type = get_light_type(id);
	idx = 0;
	if (parsing_vec(line, &light.position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &brightness_ratio, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);

	if (brightness_ratio < 0.0f || 1.0f < brightness_ratio)
		return (FAILURE);

	if (!is_color_in_range(color))
		return (FAILURE);

	if (light.type == LT_SPOT)
	{
		if (parsing_double_num(line, &light.angle, &idx) == FAILURE)
			return (FAILURE);
		if (light.angle < 0.0f || 180.0f < light.angle)
			return (FAILURE);
	}

	if (line[idx])
		return (FAILURE);

	light.illuminance = get_color_k1c1(brightness_ratio, color);

	new_list = ft_lstnew(&light);
	if (!new_list)
		return (FAILURE);
	ft_lstadd_back(&scene->light_list, new_list);

	return (SUCCESS);
}

int get_bonus_option(const char *line, t_shape *shape, size_t *idx)
{
	char	*path;

	if (ft_isdigit(line[*idx]))
	{
		shape->material.is_checker = true;
		if (parsing_color(line, &shape->material.checker_color, idx) == FAILURE)
			return (FAILURE);
		if (is_color_in_range(shape->material.diffuse_ref) == FAILURE)
			return (FAILURE);
		if (!line[*idx])
			return (SUCCESS);
	}
	path = get_identifier(line, idx);
	if (!path)
		return (FAILURE);
	if (!is_same_str(path, "null"))
	{
		if (get_img(&shape->material.texture, path) == FAILURE)
		{
			free(path);
			return (FAILURE);
		}
	}
	free(path);

	skip_delimiter(line, idx);

	path = get_identifier(line, idx);
	if (!path)
		return (FAILURE);
	if (!is_same_str(path, "null"))
	{
		if (get_img(&shape->material.bump, path) == FAILURE)
		{
			free(path);
			return (FAILURE);
		}
	}
	free(path);
	return (SUCCESS);
}

// sp   XYZ                    diameter            RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_sphere(const char *line, t_shape *shape)
{
	size_t	idx;
	float 	diameter;

	shape->type = ST_SPHERE;
	idx = 0;
	if (parsing_vec(line, &shape->data.sphere.center, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &diameter, &idx) == FAILURE)
		return (FAILURE);
	if (diameter <= 0.0f)
		return (FAILURE);
	shape->data.sphere.radius = diameter / 2.0f;

	if (parsing_color(line, &shape->material.diffuse_ref, &idx) == FAILURE)
		return (FAILURE);
	if (is_color_in_range(shape->material.diffuse_ref) == FAILURE)
		return (FAILURE);

	shape->material.is_checker = false;
	shape->material.texture.data = NULL;
	shape->material.bump.data = NULL;

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_plane(const char *line, t_shape *shape)
{
	size_t	idx;
	idx = 0;

	shape->type = ST_PLANE;
	idx = 0;
	if (parsing_vec(line, &shape->data.plane.position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &shape->data.plane.normal, &idx) == FAILURE)
		return (FAILURE);

	if (is_vec_in_normal_range(shape->data.plane.normal) == FAILURE)
		return (FAILURE);

	if (parsing_color(line, &shape->material.diffuse_ref, &idx) == FAILURE)
		return (FAILURE);
	if (is_color_in_range(shape->material.diffuse_ref) == FAILURE)
		return (FAILURE);

	shape->material.is_checker = false;
	shape->material.texture.data = NULL;
	shape->material.bump.data = NULL;

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_cylinder(const char *line, t_shape *shape)
{
	size_t	idx;
	float	diameter;

	shape->type = ST_CYLINDER;
	idx = 0;
	if (parsing_vec(line, &shape->data.cylinder.position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &shape->data.cylinder.normal, &idx) == FAILURE)
		return (FAILURE);
	if (is_vec_in_normal_range(shape->data.cylinder.normal) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &diameter, &idx) == FAILURE)
		return (FAILURE);
	if (diameter <= 0.0f)
		return (FAILURE);
	shape->data.cylinder.radius = diameter / 2.0f;

	if (parsing_double_num(line, &shape->data.cylinder.height, &idx) == FAILURE)
		return (FAILURE);
	if (shape->data.cylinder.height <= 0.0f)
		return (FAILURE);

	if (parsing_color(line, &shape->material.diffuse_ref, &idx) == FAILURE)
		return (FAILURE);
	if (is_color_in_range(shape->material.diffuse_ref) == FAILURE)
		return (FAILURE);

	shape->material.is_checker = false;
	shape->material.texture.data = NULL;
	shape->material.bump.data = NULL;

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_corn(const char *line, t_shape *shape)
{
	size_t	idx;
	float	diameter;

	shape->type = ST_CORN;
	idx = 0;
	if (parsing_vec(line, &shape->data.corn.position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &shape->data.corn.normal, &idx) == FAILURE)
		return (FAILURE);
	if (is_vec_in_normal_range(shape->data.corn.normal) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &diameter, &idx) == FAILURE)
		return (FAILURE);
	if (diameter <= 0.0f)
		return (FAILURE);
	shape->data.corn.radius = diameter / 2.0f;

	if (parsing_double_num(line, &shape->data.corn.height, &idx) == FAILURE)
		return (FAILURE);
	if (shape->data.cylinder.height <= 0.0f)
		return (FAILURE);

	if (parsing_color(line, &shape->material.diffuse_ref, &idx) == FAILURE)
		return (FAILURE);
	if (is_color_in_range(shape->material.diffuse_ref) == FAILURE)
		return (FAILURE);

	shape->material.is_checker = false;
	shape->material.texture.data = NULL;
	shape->material.bump.data = NULL;

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}


// sp   XYZ                    diameter            RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_objects(const char *line, t_scene *scene, t_identifier id)
{
	int		ret_value;
	t_shape	shape;
	t_list	*new_list;

	ret_value = FAILURE;
	if (id == id_sphere)
		ret_value = get_setting_for_sphere(line, &shape);
	else if (id == id_plane)
		ret_value = get_setting_for_plane(line, &shape);
	else if (id == id_cylinder)
		ret_value = get_setting_for_cylinder(line, &shape);
	else if (id == id_corn)
		ret_value = get_setting_for_corn(line, &shape);

	if (ret_value == FAILURE)
		return (FAILURE);

	new_list = ft_lstnew(&shape);
	if (!new_list)
		return (FAILURE);
	ft_lstadd_back(&scene->shape_list, new_list);

	return (ret_value);
}
