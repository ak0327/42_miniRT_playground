/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 22:40:36 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{
	/*1. 視線方向(eye_ray)の方向でもっとも近い物体を探す。*/
	int						res;
	t_shape					*shape;
	t_intersection_point	intp;
	size_t					i;
	t_colorf				color;
	float					nl_dot;
	float					vr_dot;
	t_vector				l;
	t_vector				r;
	t_vector				v;

	res = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);

	/*視線方向に物体があった場合*/
	if (res)
	{
		/*1. 環境光Laを計算 */
		/*2. 環境光の強さを計算してcolに入れる。 */
		color.r = scene->ambient_illuminance.r * shape->material.ambient_ref.r;
		color.g = scene->ambient_illuminance.g * shape->material.ambient_ref.g;
		color.b = scene->ambient_illuminance.b * shape->material.ambient_ref.b;

		/*3. すべての光源について処理する*/
		i = 0;
		while (i < scene->num_lights)
		{
			/*4. 入射ベクトル l を計算する（点光源の場合と平行光源の場合）。*/
			l = sub(&scene->lights[i].vector, &intp.position);
			normalize(&l);
			nl_dot = CLAMP(dot(&intp.normal, &l), 0, 1);

			/*5. 拡散反射光 diffuse を計算してcolに足し合わせる。*/
			color.r += shape->material.diffuse_ref.r * scene->lights[i].illuminance.r * nl_dot;
			color.g += shape->material.diffuse_ref.g * scene->lights[i].illuminance.g * nl_dot;
			color.b += shape->material.diffuse_ref.b * scene->lights[i].illuminance.b * nl_dot;

			/*6. 鏡面反射光 specular を計算してcolに足し合わせる*/
			if (scene->lights[i].type == LT_POINT)
			{
				r = mult(2 * nl_dot, &intp.normal);
				r = sub(&r, &l);
				normalize(&r);

				v = mult(-1, &eye_ray->direction);
				normalize(&v);

				vr_dot = dot(&v, &r);

				color.r += shape->material.specular_ref.r * scene->lights[i].illuminance.r * powf(vr_dot, shape->material.shininess);
				color.g += shape->material.specular_ref.g * scene->lights[i].illuminance.g * powf(vr_dot, shape->material.shininess);
				color.b += shape->material.specular_ref.b * scene->lights[i].illuminance.b * powf(vr_dot, shape->material.shininess);
			}
			i++;
		}

		*out_col = color;
		return (1);
	}
	return (0);
}

