/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:19:43 by takira            #+#    #+#             */
/*   Updated: 2023/04/08 22:44:43 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	get_checker_color_on_plane(t_intersection_point intp, t_shape *shape)
{
	t_colorf		color;
	int				condition_checker;
	t_vector		pos_local;
	t_texture_map	pattern_map;
	t_matrix		Tr_matrix;
	float			ra, ga, ba;
	float			rb, gb, bb;
	float			u_mag, v_mag;

	pos_local = sub(&intp.position, &shape->data.plane.position);
	u_mag = 1.0f / 50.0f;
	v_mag = 1.0f / 50.0f;
	Tr_matrix = get_tr_matrix_world2obj_yup(shape->data.plane.normal);
	pattern_map = get_planar_map(pos_local, Tr_matrix);

	ra = 0.3f; ga = 0.3f; ba = 0.3f;
	rb = 0.0f; gb = 0.0f; bb = 0.0f;

	SET_COLOR(color, ra, ga, ba)
	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
	SET_COLOR(color, rb, gb, bb)
	return (color);
}

static t_colorf	get_checker_color_on_sphere(t_intersection_point intp, t_shape *shape)
{
	t_colorf		color;
	int				condition_checker;
	t_vector		pos_local;
	t_texture_map	pattern_map;
	float			ra, ga, ba;
	float			rb, gb, bb;
	float			u_mag, v_mag;

	pos_local = sub(&intp.position, &shape->data.sphere.center);
	u_mag = 10.0f;
	v_mag = 10.0f;
	pattern_map = get_spherical_map(pos_local);
	ra = 0.2f; ga = 0.3f; ba = 0.6f;
	rb = 0.8f; gb = 0.8f; bb = 0.8f;

	SET_COLOR(color, ra, ga, ba)
	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
	SET_COLOR(color, rb, gb, bb)
	return (color);
}

static t_colorf	get_checker_color_on_cylinder(t_intersection_point intp, t_shape *shape)
{
	t_colorf		color;
	int				condition_checker;
	t_vector		pos_local;
	t_texture_map	pattern_map;
	t_matrix		Tr_matrix;
	float			ra, ga, ba;
	float			rb, gb, bb;
	float			u_mag, v_mag;

	pos_local = sub(&intp.position, &shape->data.cylinder.position);
	u_mag = 10.0f;
	v_mag = 7.0f;
	Tr_matrix = get_tr_matrix_world2obj_zup(shape->data.cylinder.normal);
	pattern_map = get_cylindrical_map(pos_local, Tr_matrix, shape->data.cylinder.height);
	ra = 0.2f; ga = 0.7f; ba = 0.2f;
	rb = 0.8f; gb = 0.8f; bb = 0.8f;

	SET_COLOR(color, ra, ga, ba)
	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
	SET_COLOR(color, rb, gb, bb)
	return (color);
}

static t_colorf	get_checker_color_on_corn(t_intersection_point intp, t_shape *shape)
{
	t_colorf		color;
	int				condition_checker;
	t_vector		pos_local;
	t_texture_map	pattern_map;
	t_matrix		Tr_matrix;
	float			ra, ga, ba;
	float			rb, gb, bb;
	float			u_mag, v_mag;

	pos_local = sub(&intp.position, &shape->data.corn.position);
	u_mag = 10.0f;
	v_mag = 10.0f;
	Tr_matrix = get_tr_matrix_world2obj_zup(shape->data.corn.normal);
	pattern_map = get_conical_map(pos_local, Tr_matrix, shape->data.corn.height);
	ra = 0.7f; ga = 0.4f; ba = 0.2f;
	rb = 0.8f; gb = 0.8f; bb = 0.8f;

	SET_COLOR(color, ra, ga, ba)
	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
	SET_COLOR(color, rb, gb, bb)
	return (color);
}

t_colorf	get_checker_color(t_intersection_point intp, t_shape *shape)
{
	t_colorf		color;
	SET_COLOR(color, 0.0f, 0.0f, 0.0f)

	if (shape->type == ST_PLANE)
		return (get_checker_color_on_plane(intp, shape));
	else if (shape->type == ST_SPHERE)
		return (get_checker_color_on_sphere(intp, shape));
	else if (shape->type == ST_CYLINDER)
		return (get_checker_color_on_cylinder(intp, shape));
	else if (shape->type == ST_CORN)
		return (get_checker_color_on_corn(intp, shape));
	return (color);
}

/* ring pattern */
//			condition_checker = (int)(floorf(sqrtf(SQR(intp.position.x) + SQR(intp.position.z)))) % 2;
//			if (condition_checker)
//			{
//				SET_COLOR(color, 0.3f, 0.3f, 0.3f);
//				color = colorf_add(&color, &color);
//			}
