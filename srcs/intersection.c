/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:28:12 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 12:40:04 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int intersection_test(const t_shape *shape,
					  const t_ray *ray,
					  t_intersection_point *out_intp)
{
	if (shape->type == ST_SPHERE)
		return (intersection_with_sphere(shape, ray, out_intp));
	if (shape->type == ST_PLANE)
		return (intersection_with_plane(shape, ray, out_intp));
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

		if ( res && intp.distance < nearest_intp.distance )
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
