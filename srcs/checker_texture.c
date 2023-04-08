/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:19:43 by takira            #+#    #+#             */
/*   Updated: 2023/04/08 14:51:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"




t_colorf	get_checker_color(t_intersection_point intp, t_shape *shape)
{
	t_colorf		color;
	int				condition_checker;
	t_vector		pos_local;
	t_texture_map	pattern_map;
	t_matrix		Tr_matrix;
	float			ra, ga, ba;
	float			rb, gb, bb;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	// checker_color, あとで関数に切り出す
	if (shape->type == ST_PLANE)
	{
		// 斜めにするとチェッカーにならない -> local座標に落とし込まないといけない？一旦これでOKとする
		condition_checker = (int)(floorf(intp.position.x / 100) + floorf(intp.position.z / 100)) % 2;
		ra = 0.3f; ga = 0.3f; ba = 0.3f;
		rb = 0.0f; gb = 0.0f; bb = 0.0f;
	}
	else if (shape->type == ST_SPHERE)
	{
		pos_local = sub(&intp.position, &shape->data.sphere.center);

		pattern_map = get_spherical_map(pos_local);
		condition_checker = (int)(floorf(pattern_map.u * 10) + floorf(pattern_map.v * 20)) % 2;
		ra = 0.2f; ga = 0.3f; ba = 0.6f;
		rb = 0.8f; gb = 0.8f; bb = 0.8f;
	}

	else if (shape->type == ST_CYLINDER)
	{
		pos_local = sub(&intp.position, &shape->data.cylinder.position);

		Tr_matrix = get_tr_matrix_world2obj(shape->data.cylinder.normal);
		pattern_map = get_cylindrical_map(pos_local, Tr_matrix, shape->data.cylinder.height);
		condition_checker = (int)(floorf(pattern_map.u * 10) + floorf(pattern_map.v * 10)) % 2;
		ra = 0.2f; ga = 0.7f; ba = 0.2f;
		rb = 0.8f; gb = 0.8f; bb = 0.8f;
	}
	else
	{
		pos_local = sub(&intp.position, &shape->data.corn.position);

		Tr_matrix = get_tr_matrix_world2obj(shape->data.corn.normal);
		pattern_map = get_cylindrical_map(pos_local, Tr_matrix, shape->data.corn.height);
		condition_checker = (int)(floorf(pattern_map.u * 10) + floorf(pattern_map.v * 10)) % 2;
		ra = 0.7f; ga = 0.4f; ba = 0.2f;
		rb = 0.8f; gb = 0.8f; bb = 0.8f;
	}
	if (condition_checker)
		SET_COLOR(color, ra, ga, ba)
	else
		SET_COLOR(color, rb, gb, bb)
	return (color);
}


/* ring pattern */
//			condition_checker = (int)(floorf(sqrtf(SQR(intp.position.x) + SQR(intp.position.z)))) % 2;
//			if (condition_checker)
//			{
//				SET_COLOR(color, 0.3f, 0.3f, 0.3f);
//				color = colorf_add(&color, &color);
//			}
