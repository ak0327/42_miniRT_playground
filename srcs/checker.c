/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:19:43 by takira            #+#    #+#             */
/*   Updated: 2023/04/02 11:41:13 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_local(t_vector pc, t_vector pi, t_vector d)
{
	t_vector	local;
	t_vector	pi_pc = sub(&pi, &pc);
	t_vector	world_normal;
	t_vector	normal;

	SET_VECTOR(world_normal, 0.0f, 1.0f, 0.0f);
	normal = sub(&world_normal, &d);

	local.x = normal.x * pi_pc.x;
	local.y = normal.y * pi_pc.y;
	local.z = normal.z * pi_pc.z;
	return (local);
}

t_colorf	get_checker_color(const t_scene *scene, const t_ray *eye_ray,
							  t_intersection_point intp, t_shape *shape)
{
	t_colorf	color;
	int			condition_checker;
	t_vector	pos_local;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	// checker_color, あとで関数に切り出す
	if (shape->type == ST_PLANE)
	{
		// 斜めにするとチェッカーにならない -> local座標に落とし込まないといけない？一旦これでOKとする
		condition_checker = (int)(floorf(intp.position.x) + floorf(intp.position.z)) % 2;
		if (condition_checker)
		{
			SET_COLOR(color, 0.3f, 0.3f, 0.3f);
			color = colorf_add(&color, &color);
		}
	}
	else if (shape->type == ST_SPHERE)
	{
		pos_local = sub(&intp.position, &shape->data.sphere.center);
//			condition_checker = (int)(floorf(intp.position.x) + floorf(intp.position.y) + floorf(intp.position.z)) % 2;
//			if (condition_checker)
//			{
//				SET_COLOR(color, 0.0f, 0.2f, 0.2f);
//				color = colorf_add(&color, &color);
//			}
		float radius = norm(&pos_local);
		float theta = atan2f(pos_local.z, pos_local.x);
		float phi = acosf(pos_local.y / radius);
		float u = 1.0f - (theta / (2.0f * (float)M_PI) + 0.5f);
		float v = 1.0f - phi / (float)M_PI;
		condition_checker = (int)(floorf(u * 15) + floorf(v * 10)) % 2;
		if (condition_checker)
		{
			SET_COLOR(color, 0.6f, 0.6f, 0.6f);
			color = colorf_add(&color, &color);
		}
		/* ring pattern */
//			condition_checker = (int)(floorf(sqrtf(SQR(intp.position.x) + SQR(intp.position.z)))) % 2;
//			if (condition_checker)
//			{
//				SET_COLOR(color, 0.3f, 0.3f, 0.3f);
//				color = colorf_add(&color, &color);
//			}
	}
	else if (shape->type == ST_CYLINDER)
	{
		pos_local = intp.position;
//		pos_local = sub(&intp.position, &shape->data.cylinder.position);
//		pos_local = get_local(shape->data.cylinder.position, intp.position, shape->data.cylinder.normal);

//		float radius = norm(&pos_local);
		float theta = atan2f(pos_local.z, pos_local.x);
//		float phi = acosf(pos_local.y / radius);
		float u = 1.0f - (theta / (2.0f * (float)M_PI) + 0.5f);
//		float v = 1.0f - phi / (float)M_PI;
		condition_checker = (int)(floorf(u * 15) + floorf(pos_local.y)) % 2;

		if (condition_checker)
		{
			SET_COLOR(color, 1.0f, 1.0f, 1.0f);
			color = colorf_add(&color, &color);
		}
	}
	return (color);
}
