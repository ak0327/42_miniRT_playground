/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_mappihng.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:45:27 by takira            #+#    #+#             */
/*   Updated: 2023/04/08 22:50:31 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	get_image_color_on_plane(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 1;
	int			img_size;
	float		u, v, w;
	float		radius, theta, phi;

	float		uu, vv;
	t_vector	pos_uv;
	t_matrix	Tr;

	t_vector	hi, d;
	float		h;

}

static t_colorf	get_image_color_on_sphere(t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 1;
	int			img_size;
	float		u, v, w;
	float		radius, theta, phi;

	float		uu, vv;
	t_vector	pos_uv;
	t_matrix	Tr;

	t_vector	hi, d;
	float		h;

	pos_local = sub(&intp.position, &shape->data.sphere.center);
	radius = norm(&pos_local);
	theta = acosf(pos_local.y / radius);

	if (radius * sinf(theta) == 0.0f)
		phi = 0.0f;
	else
		phi = acosf(pos_local.x / (radius * sinf(theta)));

	u = phi / (float)M_PI;		// 0 <= u <= 1
	v = theta / (float)M_PI;	// 0 <= v <= 1

	u *= -(float)img.width;
	v *= (float)img.height;

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
	float		u, v, w;
	float		radius, theta, phi;

	float		uu, vv;
	t_vector	pos_uv;
	t_matrix	Tr;

	t_vector	hi, d;
	float		h;

	pos_local = sub(&intp.position, &shape->data.cylinder.position);
	hi = mult(dot(&pos_local, &shape->data.cylinder.normal), &shape->data.cylinder.normal);
	d = shape->data.cylinder.normal;
	h = shape->data.cylinder.height;
	radius = shape->data.cylinder.radius;

	Tr = get_tr_matrix_world2obj(d);

	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)

	u = pos_uv.x;
	w = pos_uv.y;

	theta = acosf(u / radius);		// 0 <= theta <= pi
	uu = theta / (float)M_PI;		// 0 <= uu <= 1
	vv = w / h;						// 0 <= vv <= 1

	uu *= -(float)img.width;
	vv *= -(float)img.height;

	row = (((int)uu % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)vv % img.height) + img.height) % img.height;	// 0 <= col <= img.height

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
	float		u, v, w;
	float		radius, theta, phi;

	float		uu, vv;
	t_vector	pos_uv;
	t_matrix	Tr;

	t_vector	hi, d;
	float		h;

	pos_local = sub(&intp.position, &shape->data.corn.position);
	hi = mult(dot(&pos_local, &shape->data.corn.normal), &shape->data.corn.normal);
	d = shape->data.corn.normal;
	h = shape->data.corn.height;
	radius = shape->data.corn.radius * norm(&hi) / h;

	Tr = get_tr_matrix_world2obj(d);

	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)

	u = pos_uv.x;
	w = pos_uv.y;

	theta = acosf(u / radius);		// 0 <= theta <= pi
	uu = theta / (float)M_PI;		// 0 <= uu <= 1
	vv = w / h;						// 0 <= vv <= 1

	uu *= -(float)img.width;
	vv *= -(float)img.height;

	row = (((int)uu % img.width) + img.width) % img.width;		// 0 <= row <= img.width
	col = (((int)vv % img.height) + img.height) % img.height;	// 0 <= col <= img.height

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
