/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:13:41 by takira            #+#    #+#             */
/*   Updated: 2023/04/07 10:40:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_bump_normal(const t_scene *scene, const t_ray *eye_ray,
							t_intersection_point intp, t_shape *shape, t_img img)
{
	t_vector	bump_n;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size;
	int			u, v;
	float		fu, fv;
	t_vector	pos_local;
	float		radius, theta, phi;

	bump_n = intp.normal;

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
		bump_n.x = ((float)r - (256.0f/2.0f)) / (256.0f/2.0f);
		bump_n.z = ((float)g - (256.0f/2.0f)) / (256.0f/2.0f);
		bump_n.y = ((float)b - (256.0f/2.0f)) / (256.0f/2.0f);
		normalize(&bump_n);
		return (bump_n);
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
		bump_n.x = ((float)r - (256.0f/2.0f)) / (256.0f/2.0f);
		bump_n.z = ((float)g - (256.0f/2.0f)) / (256.0f/2.0f);
		bump_n.y = ((float)b - (256.0f/2.0f)) / (256.0f/2.0f);
		normalize(&bump_n);

		/* (u,v,w)->(x,y,z) */
		t_vector	bump_world_n;
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
		bump_world_n = Mv(Tr_matrix, bump_n);
		normalize(&bump_world_n);
		return (bump_world_n);
	}


	return (bump_n);
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
	float		u, v;
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
		t_vector	hi, d;
		float		uu, vv;
		t_vector	u_vec, v_vec;
		t_vector	eu, ev, ew;
		t_vector	ey;
		t_vector	pos_uv;
		float		l;
		t_matrix	M;

		pos_local = sub(&intp.position, &shape->data.cylinder.position);
		hi = mult(dot(&pos_local, &shape->data.cylinder.normal), &shape->data.cylinder.normal);
		d = shape->data.cylinder.normal;

//		SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
//		ew = shape->data.cylinder.normal;
//		eu = cross(&ey, &ew);
//		ev = cross(&eu, &ew);
//
//		if (ew.x == ey.x && ew.y == ey.y && ew.z == ey.z)
//		{
//			SET_VECTOR(eu, 1.0f, 0.0f, 0.0f);
//			SET_VECTOR(ev, 0.0f, 0.0f, 1.0f);
//		}
//		if (ew.x == ey.x && ew.y == -ey.y && ew.z == ey.z)
//		{
//			SET_VECTOR(eu, -1.0f, 0.0f, 0.0f);
//			SET_VECTOR(ev, 0.0f, 0.0f, -1.0f);
//		}
//
//		M = set_matrix(eu, ew, ev);	// (i,j,k)->(u,w,v)への変換matrix
////		M = transpose_matrix(M);				// (u,w,v)->(i,j,k)への変換matrix
//
//		pos_uv = Mv(M, pos_local);
//
//		u = pos_uv.x;
//		v = pos_uv.z;
//		l = sqrtf(SQR(u) + SQR(v));
//		if (l == 0)
//			theta = 0;
//		else
//			theta = acosf(u / l);
//
//		uu = theta / (float)M_PI;						// 0 <= uu <= 1
//		vv = pos_uv.y / shape->data.cylinder.height;

//		printf("(u,v)=(%f,%f), (uu,vv)=(%f,%f), theta:%f\n", u, v, uu, vv, theta * 180 / (float)M_PI);


		u_vec.x = d.y / sqrtf(SQR(d.x) + SQR(d.y));
		u_vec.y = -d.x / sqrtf(SQR(d.x) + SQR(d.y));
		u_vec.z = 0;
		normalize(&u_vec);

		v_vec = cross(&u_vec, &d);
		normalize(&v_vec);

		u = dot(&u_vec, &pos_local);
		v = dot(&v_vec, &pos_local);

		theta = atan2f(v, u);
//		uu = 1.0f - (theta / (2.0f * (float)M_PI) + 0.5f);
		uu = theta * 2 / (2.0f * (float)M_PI);
		vv = norm(&hi) / shape->data.cylinder.height;

		//		printf("(u,v)=(%f,%f), (uu,vv)=(%f,%f)\n", u, v, uu, vv);

		uu *= (float)img.width;
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
