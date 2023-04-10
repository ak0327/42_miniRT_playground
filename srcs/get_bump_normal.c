/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bump_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:13:41 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 15:36:25 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_bump_normal(t_intersection_point intp, t_shape *shape)
{
	t_colorf	img_color;
	t_vector	bump_normal_obj;
	t_vector	bump_normal_world;

	t_matrix	Tr_matrix;

	bump_normal_obj = intp.normal;
	img_color = get_img_color(intp, shape, shape->material.bump);
	bump_normal_obj.x = (img_color.r - 0.5f) / 0.5f;
	bump_normal_obj.z = (img_color.g - 0.5f) / 0.5f;
	bump_normal_obj.y = (img_color.b - 0.5f) / 0.5f;

//	Tr_matrix = get_tr_matrix_world2tangent(intp.normal);
	Tr_matrix = get_tr_matrix_world2obj_yup(intp.normal);
	Tr_matrix = transpose_matrix(Tr_matrix);
	bump_normal_world = mul_matrix_vec(Tr_matrix, bump_normal_obj);
	normalize(&bump_normal_world);
	return (bump_normal_world);
}
