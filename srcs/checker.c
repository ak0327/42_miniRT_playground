/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:19:43 by takira            #+#    #+#             */
/*   Updated: 2023/03/30 22:56:52 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	get_checker_color(const t_scene *scene, const t_ray *eye_ray,
							  t_intersection_point intp, t_shape *shape)
{
	t_colorf	color;
	int			condition_checker;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	// checker_color, あとで関数に切り出す
	if (shape->type == ST_PLANE)
	{
		// 斜めにするとチェッカーにならない -> local座標に落とし込まないといけない？一旦これでOKとする
		condition_checker = (int)(floorf(intp.position.x) + floorf(intp.position.y) + floorf(intp.position.z)) % 2;
		if (condition_checker)
		{
			SET_COLOR(color, 0.2f, 0.2f, 0.0f);
			color = colorf_add(&color, &color);
		}
	}
	else if (shape->type == ST_SPHERE)
	{
//			condition_checker = (int)(floorf(intp.position.x) + floorf(intp.position.y) + floorf(intp.position.z)) % 2;
//			if (condition_checker)
//			{
//				SET_COLOR(color, 0.0f, 0.2f, 0.2f);
//				color = colorf_add(&color, &color);
//			}

		float	theta, phi, radius;
		theta = atan2f(intp.position.x, intp.position.z);
		radius = norm(&intp.position);
		phi = acosf(intp.position.y / radius);
//			phi = acosf(intp.position.y / shape->data.sphere.radius);

		float	u = theta / (2.0f * (float)M_PI);
		float	v;
//			u = 1.0f - raw_u + 0.5f;
		v = 1.0f - phi / (float)M_PI;
		condition_checker = (int)(u + v) % 2;
//			printf("(u,v)=(%f,%f), (u+v)%%2:%d\n", u, v, condition_checker);
		if (condition_checker)
		{
			SET_COLOR(color, 0.3f, 0.3f, 0.3f);
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
		float	theta = atan2f(intp.position.x, intp.position.z);
		float	u = theta / (2.0f * (float)M_PI);
		float	v = intp.position.y;
		condition_checker = (int)(floorf(u * 20) + floorf(v * 2)) % 2;
		if (condition_checker)
		{
			SET_COLOR(color, 1.0f, 1.0f, 1.0f);
			color = colorf_add(&color, &color);
		}
	}
	return (color);
}
