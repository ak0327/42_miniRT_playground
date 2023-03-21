/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:28:12 by takira            #+#    #+#             */
/*   Updated: 2023/03/21 19:43:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	intersection_with_cylinder(t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{
	t_cylinder	*cyl;
	float		A, B, C, D;
	float		t1, t2;
	t_vector	pe_pc, pipc_n;
	t_vector	d_x_n;
	t_vector	pepc_x_n;
	t_vector	t1d, t2d;
	t_vector	pos1, pos2;
	t_vector	p1_pc, p2_pc;

	cyl = &shape->data.cylinder;
	cyl->normal = normalize_vec(&cyl->normal);
	pe_pc = sub(&ray->start, &cyl->position);

	d_x_n = cross(&ray->direction, &cyl->normal);
	pepc_x_n = cross(&pe_pc, &cyl->normal);
	A = SQR(norm(&d_x_n));
	B = 2 * dot(&d_x_n, &pepc_x_n);
	C = SQR(norm(&pepc_x_n)) - SQR(cyl->radius);

	D = SQR(B) - 4 * A * C;

	if (A == 0)
		return (0);
	if (D < 0)
		return (0);

	t1 = (float) (-B - sqrtf(D)) / (2 * A);
	t2 = (float) (-B + sqrtf(D)) / (2 * A);

	if (t1 <= 0 && t2 <= 0)
		return (0);

	if (!out_intp)
		return (0);

	t1d = mult(t1, &ray->direction);
	pos1 = add(&ray->start, &t1d);
	p1_pc = sub(&pos1, &cyl->position);

	if (0 <= dot(&p1_pc, &cyl->normal) && dot(&p1_pc, &cyl->normal) <= cyl->height)
	{
		out_intp->distance = t1;
		out_intp->position = pos1;
		pipc_n = mult(dot(&p1_pc, &cyl->normal), &cyl->normal);
		out_intp->normal = sub(&p1_pc, &pipc_n);
		normalize(&out_intp->normal);
		return (1);
	}

	t2d = mult(t2, &ray->direction);
	pos2 = add(&ray->start, &t2d);
	p2_pc = sub(&pos2, &cyl->position);
	if (0 <= dot(&p2_pc, &cyl->normal) && dot(&p2_pc, &cyl->normal) <= cyl->height)
	{
		out_intp->distance = t2;
		out_intp->position = pos2;
		pipc_n = mult(dot(&p2_pc, &cyl->normal), &cyl->normal);
		out_intp->normal = sub( &pipc_n, &p2_pc);
		normalize(&out_intp->normal);
		return (1);
	}
	return (0);
}

static float	sign(t_vector p1, t_vector p2, t_vector p3)
{
	return ((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
}

static int	intersection_with_triangle(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{
	const t_triangle	*tri = &shape->data.triangle;
	float 				dn_dot = dot(&ray->direction, &tri->normal);
	t_vector			s_p;
	float				t;
	t_vector			td;

	bool				b1, b2, b3;
	t_vector			pt = add(&ray->start, &ray->direction);

	if (dn_dot == 0)
		return (0);

	s_p = sub(&ray->start, &tri->position);
	t = -dot(&s_p, &tri->normal) / dn_dot;

	if (t <= 0)
		return (0);

	b1 = sign(pt, tri->p1, tri->p2) < 0.0f;
	b2 = sign(pt, tri->p2, tri->p3) < 0.0f;
	b3 = sign(pt, tri->p3, tri->p1) < 0.0f;

	if (!((b1 == b2) && (b2 == b3)))
		return (0);

	if (!out_intp)
		return (0);

	out_intp->distance = t;
	td = mult(t, &ray->direction);
	out_intp->position = add(&ray->start, &td);
	out_intp->normal = tri->normal;

	return (1);
}

static int	intersection_with_corn(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{
	const t_corn	*corn = &shape->data.corn;
	t_vector		d = ray->direction;
	t_vector		s = ray->start;
	float			A, B, C, D;
	float			r = corn->radius;
	float			h = corn->height;
	t_vector		c = corn->position;
	float			ax, ay, az;

	t_vector		int_p;
	float			t;

	ax = s.x - c.x;
	ay = s.y - h - c.y;
	az = s.z - c.z;

	A = SQR(d.x) - SQR(r / h) * SQR(d.y) + SQR(d.z);
	B = 2 * d.x * ax - 2 * SQR(r / h) * d.y * ay + 2 * d.z * az;
	C = SQR(ax) - SQR(r/ h) * SQR(ay) + SQR(az);

	D = SQR(B) - 4 * A * C;

	t = -1.0f;

	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		float t1 = (float) (-B + sqrtf(D)) / (2 * A);
		float t2 = (float) (-B - sqrtf(D)) / (2 * A);
		if (t1 > 0) t = t1;
		if (t2 > 0 && t2 < t) t = t2;
	}

	if (t <= 0)
		return (0);
	if (!out_intp)
		return (0);
	int_p = vec_calc(1.0f, &s, t, &d);
	if (!(0 <= int_p.y - c.y && int_p.y - c.y <= h)) // ここを2/hにすれば円錐台になる
		return (0);

	out_intp->position = int_p;
	out_intp->normal.x = 2 * (int_p.x - c.x);
	out_intp->normal.y = 2 * (r / h) * (int_p.y - h - c.y);
	out_intp->normal.z = 2 * (int_p.z - c.z);
	normalize(&out_intp->normal);
	return (1);
}

/* 上向きはOK */
//static int	intersection_with_corn(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
//{
//	const t_corn	*corn = &shape->data.corn;
//	t_vector		d = ray->direction;
//	t_vector		s = ray->start;
//	float			A, B, C, D;
//	float			r = corn->radius;
//	float			h = corn->height;
//	t_vector		c = corn->position;
//	float			ax, ay, az;
//
//	t_vector		int_p;
//	float			t;
//
//	ax = s.x - c.x;
//	ay = s.y - h - c.y;
//	az = s.z - c.z;
//
//	A = SQR(d.x) - SQR(r / h) * SQR(d.y) + SQR(d.z);
//	B = 2 * d.x * ax - 2 * SQR(r / h) * d.y * ay + 2 * d.z * az;
//	C = SQR(ax) - SQR(r/ h) * SQR(ay) + SQR(az);
//
//	D = SQR(B) - 4 * A * C;
//
//	t = -1.0f;
//
//	if (D == 0)
//		t = -B / (2 * A);
//	else if (D > 0)
//	{
//		float t1 = (float) (-B + sqrtf(D)) / (2 * A);
//		float t2 = (float) (-B - sqrtf(D)) / (2 * A);
//		if (t1 > 0) t = t1;
//		if (t2 > 0 && t2 < t) t = t2;
//	}
//
//	if (t <= 0)
//		return (0);
//	if (!out_intp)
//		return (0);
//	int_p = vec_calc(1.0f, &s, t, &d);
//	if (!(0 <= int_p.y - c.y && int_p.y - c.y <= h)) // ここを2/hにすれば円錐台になる
//		return (0);
//
//	out_intp->position = int_p;
//	out_intp->normal.x = 2 * (int_p.x - c.x);
//	out_intp->normal.y = 2 * (r / h) * (int_p.y - h - c.y);
//	out_intp->normal.z = 2 * (int_p.z - c.z);
//	normalize(&out_intp->normal);
//	return (1);
//}

static int	intersection_with_hyperboloid(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{

	return (1);
}

static int	intersection_with_paraboloid(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{

	return (1);
}

static int	intersection_with_sphere(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{
	const t_sphere	*sph = &shape->data.sphere;
	t_vector		pe_pc;
	float			A, B, C, D;
	float			t;
	t_vector		td;

	pe_pc = sub(&ray->start, &sph->center);
	A = dot(&ray->direction, &ray->direction);
	B = 2 * dot(&ray->direction, &pe_pc);
	C = dot(&pe_pc, &pe_pc) - SQR(sph->radius);

	D = SQR(B) - 4 * A * C;

	t = -1.0f;
	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		float t1 = (float) (-B + sqrtf(D)) / (2 * A);
		float t2 = (float) (-B - sqrtf(D)) / (2 * A);
		if (t1 > 0) t = t1;
		if (t2 > 0 && t2 < t) t = t2;
	}

	if (t <= 0)
		return (0);
	if (!out_intp)
		return (0);

	out_intp->distance = t;
	td = mult(t, &ray->direction);
	out_intp->position = add(&ray->start, &td);
	out_intp->normal = sub(&out_intp->position, &sph->center);
	normalize(&out_intp->normal);
	return (1);
}

static int	intersection_with_plane(const t_shape *shape, const t_ray *ray, t_intersection_point *out_intp)
{
	const t_plane	*pln = &shape->data.plane;
	float 			dn_dot = dot(&ray->direction, &pln->normal);
	t_vector		s_p;
	float			t;
	t_vector		td;

	if (dn_dot == 0)
		return (0);

	s_p = sub(&ray->start, &pln->position);
	t = -dot(&s_p, &pln->normal) / dn_dot;

	if (t <= 0)
		return (0);

	if (!out_intp)
		return (0);

	out_intp->distance = t;
	td = mult(t, &ray->direction);
	out_intp->position = add(&ray->start, &td);
	out_intp->normal = pln->normal;
	return (1);
}

int intersection_test(t_shape *shape,
					  const t_ray *ray,
					  t_intersection_point *out_intp)
{
	if (shape->type == ST_PLANE)
		return (intersection_with_plane(shape, ray, out_intp));
	if (shape->type == ST_SPHERE)
		return (intersection_with_sphere(shape, ray, out_intp));
	if (shape->type == ST_CYLINDER)
		return (intersection_with_cylinder(shape, ray, out_intp));
	if (shape->type == ST_CORN)
		return (intersection_with_corn(shape, ray, out_intp));
	if (shape->type == ST_TRIANGLE)
		return (intersection_with_triangle(shape, ray, out_intp));
	return (0);
}

int get_nearest_shape(const t_scene *scene,
					  const t_ray *ray,
					  float max_dist,
					  int exit_once_found,
					  t_shape **out_shape,
					  t_intersection_point *out_intp)
{
	size_t					i;
	t_shape					*nearest_shape = NULL;
	t_intersection_point	nearest_intp;
	t_intersection_point	intp;
	int						res;

	nearest_intp.distance = max_dist;

	i = 0;
	while (i < scene->num_shapes)
	{
		res = intersection_test(&scene->shapes[i], ray, &intp);

		if (res && intp.distance < nearest_intp.distance)
		{
			nearest_shape = &scene->shapes[i];
			nearest_intp = intp;
			if (exit_once_found)
				break;
		}
		i++;
	}

	if (!nearest_shape)
		return (0);
	if (out_shape)
		*out_shape = nearest_shape;
	if (out_intp)
		*out_intp = nearest_intp;
	return (1);
}
