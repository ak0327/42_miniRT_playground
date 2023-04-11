/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:45:27 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 09:31:28 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	get_image_color_on_plane(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf		color;
	t_vector		pos_local;
	int				r, g, b;
	size_t			row, col, idx;
	int				frequency = 3;
	t_matrix		Tr_matrix;
	t_texture_map	map;

	pos_local = sub(&intp.position, &shape->data.plane.position);
	Tr_matrix = get_tr_matrix_world2obj_yup(shape->data.plane.normal);
	map = get_planar_map(pos_local, Tr_matrix);

	row = ((((int)map.u * frequency) % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((-(int)map.v * frequency) % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

static t_colorf	get_image_color_on_sphere(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf		color;
	int				r, g, b;
	size_t			row, col, idx;
	int				frequency = 1;
	t_texture_map	map;

	map = get_spherical_map(intp.position, shape->data.sphere.center);

	map.u *= (float)img.width * (float)frequency;
	map.v *= (float)img.height * (float)frequency;

	row = (((int)map.u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)map.v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

static t_colorf	get_image_color_on_cylinder(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf		color;
	t_vector		pos_local;
	int				r, g, b;
	size_t			row, col, idx;
	t_matrix		Tr_matrix;
	int				frequency = 1;
	t_texture_map	map;

	pos_local = sub(&intp.position, &shape->data.cylinder.position);
	Tr_matrix = get_tr_matrix_world2obj_yup(shape->data.cylinder.normal);

	map = get_cylindrical_map(pos_local, Tr_matrix, shape->data.cylinder.height);
	map.u *= (float)img.width * (float)frequency;
	map.v *= -(float)img.height * (float)frequency;

	row = (((int)map.u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)map.v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

static t_colorf	get_image_color_on_corn(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf		color;
	t_vector		pos_local;
	int				r, g, b;
	size_t			row, col, idx;
	t_matrix		Tr_matrix;
	t_texture_map	map;
	int				frequency = 1;

	pos_local = sub(&intp.position, &shape->data.corn.position);

	Tr_matrix = get_tr_matrix_world2obj_yup(shape->data.corn.normal);

	map = get_conical_map(pos_local, Tr_matrix, shape->data.corn.height);
	map.u *= (float)img.width * (float)frequency;
	map.v *= -(float)img.height * (float)frequency;

	row = (((int)map.u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)map.v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

t_colorf	get_img_color(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	if (shape->type == ST_PLANE)
		return (get_image_color_on_plane(intp, shape, img));
	else if (shape->type == ST_SPHERE)
		return (get_image_color_on_sphere(intp, shape, img));
	else if (shape->type == ST_CYLINDER)
		return (get_image_color_on_cylinder(intp, shape, img));
	else if (shape->type == ST_CORN)
		return (get_image_color_on_corn(intp, shape, img));
	return (color);
}
