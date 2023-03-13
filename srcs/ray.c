/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/03/13 10:35:31 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{
	/*1. 視線方向(eye_ray)の方向でもっとも近い物体を探す。*/
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
	t_ray					shawod_ray;
	float					dist;
	t_vector				vec_pi_to_light;

	int_res = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);

	/*視線方向に物体があった場合*/
	if (int_res)
	{
		/*1. 環境光Laを計算 */
		/*2. 環境光の強さを計算してcolに入れる。 */
		SET_COLOR(color, 0.0, 0.0, 0.0);
		color.r = scene->ambient_illuminance.r * shape->material.ambient_ref.r;
		color.g = scene->ambient_illuminance.g * shape->material.ambient_ref.g;
		color.b = scene->ambient_illuminance.b * shape->material.ambient_ref.b;

		/*3. すべての光源について処理する*/
		i = 0;
		while (i < scene->num_lights)
		{
			/*4. 入射ベクトル light_dir を計算する（点光源の場合と平行光源の場合）。*/
			light = &scene->lights[i];
			if (light->type == LT_POINT)	// 点光源
				light_dir = sub(&light->vector, &intp.position);
			else
				light_dir = light->vector;	// 平行光源

			normalize(&light_dir);
			nl_dot = CLAMP(dot(&intp.normal, &light_dir), 0, 1);

			/* シャドウレイ */
			shawod_ray.start = mult(EPSILON, &light_dir);
			shawod_ray.start = add(&intp.position, &shawod_ray.start);
			shawod_ray.direction = light_dir;
			if (light->type == LT_POINT)
			{
				vec_pi_to_light = sub(&light->vector, &intp.position);
				dist = norm(&vec_pi_to_light);
			}
			else
				dist = FLT_MAX;

			shadow_int_res = get_nearest_shape(scene, &shawod_ray, dist, 1, NULL, NULL);
			if (!shadow_int_res)
			{

				/*5. 拡散反射光 diffuse を計算してcolに足し合わせる。*/
				color.r += shape->material.diffuse_ref.r * light->illuminance.r * nl_dot;
				color.g += shape->material.diffuse_ref.g * light->illuminance.g * nl_dot;
				color.b += shape->material.diffuse_ref.b * light->illuminance.b * nl_dot;

				/*6. 鏡面反射光 specular を計算してcolに足し合わせる*/
				if (nl_dot > 0)
				{
					/* 正反射ベクトルの計算 */
					ref_dir = mult(2 * nl_dot, &intp.normal);
					ref_dir = sub(&ref_dir, &light_dir);
					normalize(&ref_dir);

					/* 視線ベクトルの逆ベクトルの計算 */
					inv_eye_dir = mult(-1, &eye_ray->direction);
					normalize(&inv_eye_dir);

					vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
					vr_dot_pow = powf(vr_dot, shape->material.shininess);

					/* 鏡面反射光の計算 */
					color.r += shape->material.specular_ref.r * light->illuminance.r * vr_dot_pow;
					color.g += shape->material.specular_ref.g * light->illuminance.g * vr_dot_pow;
					color.b += shape->material.specular_ref.b * light->illuminance.b * vr_dot_pow;

			}
			}
			i++;
		}
		*out_col = color;
		return (1);
	}
	return (0);
}

