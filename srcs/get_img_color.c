/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:45:27 by takira            #+#    #+#             */
/*   Updated: 2023/04/09 14:43:55 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	get_image_color_on_plane(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf		color;
	t_vector		pos_local;
	int				r, g, b;
	size_t			row, col, idx;
	int				put_size = 1;
	int				img_size;
	t_matrix		Tr_matrix;
	t_texture_map	pattern_map;

	pos_local = sub(&intp.position, &shape->data.plane.position);
	Tr_matrix = get_tr_matrix_world2obj_yup(shape->data.plane.normal);
	pattern_map = get_planar_map(pos_local, Tr_matrix);

	row = ((((int)pattern_map.u * put_size) % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((-(int)pattern_map.v * put_size) % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

static t_colorf	get_image_color_on_sphere(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 1;
	int			img_size;
	float		u, v;
	float		radius, theta, phi;
	int			frequency = 1;

	pos_local = sub(&intp.position, &shape->data.sphere.center);
	radius = norm(&pos_local);
	theta = acosf(pos_local.y / radius);

	if (radius * sinf(theta) == 0.0f)
		phi = 0.0f;
	else
		phi = acosf(pos_local.x / (radius * sinf(theta)));

	u = phi / (float)M_PI;		// 0 <= u <= 1
	v = theta / (float)M_PI;	// 0 <= v <= 1

	u *= -(float)img.width * (float)frequency;
	v *= (float)img.height * (float)frequency;

	row = (((int)u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

static t_colorf	get_image_color_on_cylinder(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 1;
	int			img_size;
	float		radius, theta;
	float		u, v;
	t_vector	pos_uv;
	t_matrix	Tr_matrix;
	int			frequency = 1;

	pos_local = sub(&intp.position, &shape->data.cylinder.position);
	radius = shape->data.cylinder.radius;

	Tr_matrix = get_tr_matrix_world2obj_zup(shape->data.cylinder.normal);

	pos_uv = mul_matrix_vec(Tr_matrix, pos_local);	// pos(x,y,z)->pos(u,v,w)

	theta = acosf(pos_uv.x / radius);				// 0 <= theta <= pi
	u = theta / (float)M_PI;						// 0 <= u <= 1
	v = pos_uv.y / shape->data.cylinder.height;		// 0 <= v <= 1

	u *= -(float)img.width * (float)frequency;
	v *= -(float)img.height * (float)frequency;

	row = (((int)u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	r = img.data[idx++];
	g = img.data[idx++];
	b = img.data[idx];
	SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
	return (color);
}

static t_colorf	get_image_color_on_corn(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 1;
	int			img_size;
	float		u, v;
	float		radius, theta;

	t_vector	pos_uv;
	t_matrix	Tr_matrix;

	t_vector	hi;
	int			frequency = 1;

	pos_local = sub(&intp.position, &shape->data.corn.position);
	hi = mult(dot(&pos_local, &shape->data.corn.normal), &shape->data.corn.normal);
	radius = shape->data.corn.radius * norm(&hi) / shape->data.corn.height;

	Tr_matrix = get_tr_matrix_world2obj_zup(shape->data.corn.normal);
	pos_uv = mul_matrix_vec(Tr_matrix, pos_local);	// pos(x,y,z)->pos(u,v,w)

	theta = acosf(pos_uv.x / radius);				// 0 <= theta <= pi
	u = theta / (float)M_PI;						// 0 <= u <= 1
	v = pos_uv.y / shape->data.corn.height;			// 0 <= v <= 1

	u *= -(float)img.width * (float)frequency;
	v *= -(float)img.height * (float)frequency;

	row = (((int)u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

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
