/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:13:41 by takira            #+#    #+#             */
/*   Updated: 2023/04/07 12:28:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_bump_normal(const t_scene *scene, const t_ray *eye_ray,
							t_intersection_point intp, t_shape *shape, t_img img)
{
	t_vector	bump_normal_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size;
	int			u, v;
	float		fu, fv;
	t_vector	pos_local;
	float		radius, theta, phi;

	bump_normal_local = intp.normal;

	if (shape->type == ST_PLANE)
	{
		u = (int)intp.position.x;
		v = (int)intp.position.z;
//		u = -u;//todo: 影の方向 これで良さそう なぜ？
		v = -v;

		put_size = 10;
		row = (((u * put_size)  % img.width) + img.width) % img.width;
		col = (((v * put_size) % img.height) + img.height) % img.height;

		idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
		r = img.data[idx++];
		g = img.data[idx++];
		b = img.data[idx];
		bump_normal_local.x = ((float)r - (256.0f / 2.0f)) / (256.0f / 2.0f);
		bump_normal_local.z = ((float)g - (256.0f / 2.0f)) / (256.0f / 2.0f);
		bump_normal_local.y = ((float)b - (256.0f / 2.0f)) / (256.0f / 2.0f);
		normalize(&bump_normal_local);
		return (bump_normal_local);
	}
	if (shape->type == ST_SPHERE)
	{
		pos_local = sub(&intp.position, &shape->data.sphere.center);
		radius = norm(&pos_local);
		theta = acosf(pos_local.y / radius);

		if (radius * sinf(theta) == EPSILON)
			phi = 0.0f;
		else
			phi = acosf(pos_local.x / (radius * sinf(theta)));

		fu = phi / (float)M_PI;		// 0 <= fu <= 1
		fv = theta / (float)M_PI;	// 0 <= fv <= 1

//		img_size = 2000;
		int	frequency = 1;
		fu *= -(float)img.width * (float)frequency;
		fv *= (float)img.height * (float)frequency;

		row = (((int)fu % img.width) + img.width) % img.width;		// 0 <= row <= img.width
		col = (((int)fv % img.height) + img.height) % img.height;	// 0 <= col <= img.height

		idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
		r = img.data[idx++];
		g = img.data[idx++];
		b = img.data[idx];
		bump_normal_local.x = ((float)r - (256.0f / 2.0f)) / (256.0f / 2.0f);
		bump_normal_local.z = ((float)g - (256.0f / 2.0f)) / (256.0f / 2.0f);
		bump_normal_local.y = ((float)b - (256.0f / 2.0f)) / (256.0f / 2.0f);
		normalize(&bump_normal_local);

		/* (u,v,w)->(x,y,z) */
		t_vector	bump_normal_world;
		t_vector	eu, ev, ew;
		t_vector	ey;
		t_matrix	Tr_matrix;

		SET_VECTOR(ey, 0.0f, 1.0f, 0.0f)
		ew = intp.normal;
		eu = cross(&ew, &ey);
		normalize(&eu);
		ev = cross(&eu, &ew);
		normalize(&ev);

		if (ew.x == ey.x && ew.y == ey.y && ew.z == ey.z)
		{
			SET_VECTOR(eu, 1.0f, 0.0f, 0.0f);
			SET_VECTOR(ev, 0.0f, 0.0f, 1.0f);
		}
		if (ew.x == ey.x && ew.y == -ey.y && ew.z == ey.z)
		{
			SET_VECTOR(eu, -1.0f, 0.0f, 0.0f);
			SET_VECTOR(ev, 0.0f, 0.0f, -1.0f);
		}

		Tr_matrix = set_matrix(eu, ew, ev);
		Tr_matrix = transpose_matrix(Tr_matrix);
		bump_normal_world = Mv(Tr_matrix, bump_normal_local);
		normalize(&bump_normal_world);
		return (bump_normal_world);
	}


	return (bump_normal_local);
}


t_colorf	get_img_color(const t_scene *scene, const t_ray *eye_ray,
						  t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 1;
	int			img_size;
	float		u, v, w;
	float		radius, theta, phi;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
//	if (shape->type == ST_PLANE)
//	{
//		u = intp.position.x;
//		v = intp.position.z;
//		v = -v;
//
//		row = ((((int)u * put_size)  % img.width) + img.width) % img.width;
//		col = ((((int)v * put_size) % img.height) + img.height) % img.height;
//
//		idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
//		r = img.data[idx++];
//		g = img.data[idx++];
//		b = img.data[idx];
//		SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
//		return (color);
//	}
	if (shape->type == ST_SPHERE)
	{
		pos_local = sub(&intp.position, &shape->data.sphere.center);
		radius = norm(&pos_local);
		theta = acosf(pos_local.y / radius);

		if (radius * sinf(theta) == EPSILON)
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
	if (shape->type == ST_CYLINDER)
 	{
		/* u,v */
		float		uu, vv, ww;
		t_vector	eu, ev, ew;
		t_vector	ex, ey;
		t_vector	pos_uv;
		t_matrix	M;

		pos_local = sub(&intp.position, &shape->data.cylinder.position);

		SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
		SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);

		ew = shape->data.cylinder.normal;
		ev = cross(&ex, &ew);
		normalize(&ev);
		eu = cross(&ew, &ev);
		normalize(&eu);

		if (ew.x == ex.x && ew.y == ex.y && ew.z == ex.z)
		{
			SET_VECTOR(eu, 0.0f, -1.0f, 0.0f);
			SET_VECTOR(ev, 0.0f, 0.0f, 1.0f);
		}
		if (ew.x == -ex.x && ew.y == ex.y && ew.z == ex.z)
		{
			SET_VECTOR(eu, 0.0f, 1.0f, 0.0f);
			SET_VECTOR(ev, 0.0f, 0.0f, 1.0f);
		}

		M = set_matrix(eu, ew, ev);	// (i,j,k)->(u,w,v)への変換matrix
//		M = transpose_matrix(M);				// (u,w,v)->(i,j,k)への変換matrix

		pos_uv = Mv(M, pos_local);

		u = pos_uv.x; //このuは結局xになっているのでは？
		v = pos_uv.z;
		w = pos_uv.y;

		theta = acosf(u / shape->data.cylinder.radius);
		uu = theta / (float)M_PI;
		vv = w / shape->data.cylinder.height;

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
	return (color);
}
