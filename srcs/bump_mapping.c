/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:13:41 by takira            #+#    #+#             */
/*   Updated: 2023/04/09 14:23:41 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	get_img_color_for_plane(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	int			u, v, put_size;
	size_t		row, col, idx;

	u = (int)intp.position.x;
	v = (int)intp.position.z;
	v = -v;

	put_size = 1;
	row = (((u * put_size)  % img.width) + img.width) % img.width;
	col = (((v * put_size) % img.height) + img.height) % img.height;

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	color.r = (float)img.data[idx++];
	color.g = (float)img.data[idx++];
	color.b = (float)img.data[idx];
	return (color);
}

static t_colorf	get_img_color_for_sphere(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf		color;
	size_t			row, col, idx;
	int				frequency;
	t_vector		pos_local;
	t_texture_map	pattern_map;

	pos_local = sub(&intp.position, &shape->data.sphere.center);

	frequency = 1;

	pattern_map = get_spherical_map(pos_local);
	pattern_map.u *= -(float)img.width * (float)frequency;
	pattern_map.v *= (float)img.height * (float)frequency;

	row = (((int)pattern_map.u % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)pattern_map.v % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	color.r = (float)img.data[idx++];
	color.g = (float)img.data[idx++];
	color.b = (float)img.data[idx];

	return (color);
}

static t_colorf	get_img_color_for_cylinder(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;

	size_t		row, col, idx;
	int			frequency;

	float		uu, vv;
	float		radius, theta, h;

	t_vector	pos_uv;
	t_vector	pos_local;
	t_vector	hi, d;

	t_matrix	Tr_matrix;

	pos_local = sub(&intp.position, &shape->data.cylinder.position);
	d = shape->data.cylinder.normal;
	h = shape->data.cylinder.height;
	radius = shape->data.cylinder.radius;

	Tr_matrix = get_tr_matrix_world2obj_zup(d);
	pos_uv = mul_matrix_vec(Tr_matrix, pos_local);			// pos(x,y,z)->pos(u,v,w)

	theta = acosf(pos_uv.x / radius);	// 0 <= theta <= pi
	uu = theta / (float)M_PI;			// 0 <= uu <= 1
	vv = pos_uv.y / h;					// 0 <= vv <= 1

	frequency = 1;
	uu *= -(float)img.width * (float)frequency;
	vv *= -(float)img.height * (float)frequency;

	row = (((int)uu % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)vv % img.height) + img.height) % img.height;	// 0 <= col <= img.height


	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	color.r = (float)img.data[idx++];
	color.g = (float)img.data[idx++];
	color.b = (float)img.data[idx];

	return (color);

}

static t_colorf	get_img_color_for_corn(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;

	size_t		row, col, idx;
	int			frequency;

	float		uu, vv;
	float		radius, theta, h;

	t_vector	pos_uv;
	t_vector	pos_local;
	t_vector	hi, d;

	t_matrix	Tr_matrix;

	pos_local = sub(&intp.position, &shape->data.corn.position);
	hi = mult(dot(&pos_local, &shape->data.corn.normal), &shape->data.corn.normal);
	d = shape->data.corn.normal;
	h = shape->data.corn.height;
	radius = shape->data.corn.radius * norm(&hi) / h;

	Tr_matrix = get_tr_matrix_world2obj_zup(d);
	pos_uv = mul_matrix_vec(Tr_matrix, pos_local);			// pos(x,y,z)->pos(u,v,w)

	theta = acosf(pos_uv.x / radius);	// 0 <= theta <= pi
	uu = theta / (float)M_PI;			// 0 <= uu <= 1
	vv = pos_uv.y / h;					// 0 <= vv <= 1

	frequency = 1;
	uu *= -(float)img.width * (float)frequency;
	vv *= -(float)img.height * (float)frequency;

	row = (((int)uu % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)vv % img.height) + img.height) % img.height;	// 0 <= col <= img.height

	idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
	color.r = (float)img.data[idx++];
	color.g = (float)img.data[idx++];
	color.b = (float)img.data[idx];

	return (color);
}

t_vector	get_bump_normal(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	img_color;
	t_vector	bump_normal_obj;
	t_vector	bump_normal_world;

	t_matrix	Tr_matrix;

	bump_normal_obj = intp.normal;

	SET_VECTOR(bump_normal_world, 0.0f, 0.0f, 0.0f);
	if (shape->type == ST_PLANE)
		img_color = get_img_color_for_plane(intp, shape, img);
	else if (shape->type == ST_SPHERE)
		img_color = get_img_color_for_sphere(intp, shape, img);
	else if (shape->type == ST_CYLINDER)
		img_color = get_img_color_for_cylinder(intp, shape, img);
	else if (shape->type == ST_CORN)
		img_color = get_img_color_for_corn(intp, shape, img);
	else
		return (bump_normal_world);

	bump_normal_obj.x = (img_color.r - (256.0f / 2.0f)) / (256.0f / 2.0f);
	bump_normal_obj.z = (img_color.g - (256.0f / 2.0f)) / (256.0f / 2.0f);
	bump_normal_obj.y = (img_color.b - (256.0f / 2.0f)) / (256.0f / 2.0f);

//	Tr_matrix = get_tr_matrix_world2tangent(intp.normal);
	Tr_matrix = get_tr_matrix_world2obj_yup(intp.normal);
	Tr_matrix = transpose_matrix(Tr_matrix);
	bump_normal_world = mul_matrix_vec(Tr_matrix, bump_normal_obj);
	normalize(&bump_normal_world);
	return (bump_normal_world);
}
