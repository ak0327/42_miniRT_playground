/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/03/13 22:26:40 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recursive_raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level)
{
	int						int_res;	// 交差判定の結果
	t_shape					*shape;	// 交差した物体へのポインタ
	t_intersection_point	intp;	// 交点

	size_t					i;
	t_colorf				color;

	t_light					*light;
	t_vector				light_dir; 	// 入射ベクトル
	float					nl_dot;		// 法線ベクトルと入射ベクトルの内積
	t_vector				ref_dir;
	t_vector				inv_eye_dir;
	float					vr_dot;
	float					vr_dot_pow;

	int 					shadow_int_res;
	t_ray					shadow_ray;
	float					dist;
	t_vector				vec_pi_to_light;

	/* 再帰呼び出し回数が制限回数以上の場合は終了 */
	if (recursion_level > MAX_RECURSION)
		return (0);

	/*1. 視線方向(eye_ray)の方向でもっとも近い物体を探す。*/
	int_res = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);

	/*視線方向に物体がなかった場合*/
	if (!int_res)
		return (0);

	/* 視線方向に物体があった場合 */

	/* 1. 環境光Laを計算しcolに入れる */
	SET_COLOR(color, 0.0, 0.0, 0.0);
	color = colorf_mul(&color, 1, &scene->ambient_illuminance, 1, &shape->material.ambient_ref);

	/* すべての光源について処理する */
	i = 0;
	while (i < scene->num_lights)
	{
		/* 入射ベクトル light_dir を計算する（点光源の場合と平行光源の場合） */
		light = &scene->lights[i];
		if (light->type == LT_POINT)	// 点光源
			light_dir = sub(&light->vector, &intp.position);
		else
			light_dir = light->vector;	// 平行光源

		normalize(&light_dir);
		nl_dot = CLAMP(dot(&intp.normal, &light_dir), 0, 1);

		/* shadow_rayを計算 */
		shadow_ray.start = vec_calc(1, &intp.position, EPSILON, &light_dir);
		shadow_ray.direction = light_dir;
		if (light->type == LT_POINT)
		{
			vec_pi_to_light = sub(&light->vector, &intp.position);
			dist = norm(&vec_pi_to_light) - EPSILON;
		}
		else
			dist = FLT_MAX;

		shadow_int_res = get_nearest_shape(scene, &shadow_ray, dist, 1, NULL, NULL);

		/* shadow_rayが物体に遮られなかった場合 */
		if (!shadow_int_res)
		{
			/* 拡散反射光 diffuse を計算してcolに足し合わせる */
			color = colorf_mul(&color, 1, &shape->material.diffuse_ref, nl_dot,&light->illuminance);

			/* 鏡面反射光 specular を計算してcolに足し合わせる */
			if (nl_dot > 0)
			{
				/* 正反射ベクトルの計算 */
				ref_dir = vec_calc(2 * nl_dot, &intp.normal, -1, &light_dir);
				normalize(&ref_dir);

				/* 視線ベクトルの逆ベクトルの計算 */
				inv_eye_dir = mult(-1, &eye_ray->direction);
				normalize(&inv_eye_dir);

				vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
				vr_dot_pow = powf(vr_dot, shape->material.shininess);

				/* 鏡面反射光の計算 */
				color = colorf_mul(&color, 1, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
			}
		}

		i++;
	}
	*out_col = color;
	return (1);
}

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{
	return (recursive_raytrace(scene, eye_ray, out_col, 0));
}
