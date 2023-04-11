/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:36:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 14:57:54 by takira           ###   ########.fr       */
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

	if (parsing_double_num(line, &camera->d_fov_deg) == FAILURE)
		return (FAILURE);

	if (line[idx])
		return (FAILURE);

	if (!is_vec_in_normal_range(camera->dir))
		return (FAILURE);

	if (camera->d_fov_deg < 0.0 || 180.0 < camera->d_fov_deg)
		return (FAILURE);

	return (SUCCESS);
}

// A   lightning_ratio[0,1]   RGB[0,255]
int	get_setting_for_ambient(const char *line, t_scene *scene)
{

	return (SUCCESS);
}

// L   XYZ   brightness_ratio[0,1]   RGB[0,255]
// sl  XYZ   brightness_ratio[0,1]   RGB[0,255]   angle[0,180]
int get_setting_for_lights(const char *line, t_scene *scene)
{

	return (SUCCESS);
}

// sp   XYZ   diameter                             RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_objects(const char *line, t_scene *scene)
{

	return (SUCCESS);
}