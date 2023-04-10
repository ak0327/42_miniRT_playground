/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:12:18 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 13:12:19 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf calc_diffuse_reflection(const t_scene *scene, const t_ray *eye_ray,
						  t_intersection_point intp, t_shape *shape)
{
	t_colorf	color, checker_col, img_col;
	size_t		i;
	t_light		*light;
	t_vector	ref_dir, dir_pos_to_light, inv_eye_dir, vec_pi_to_light, normal;
	float		nl_dot, vr_dot, vr_dot_pow, dist;
	int 		shadow_int_res;
	t_ray		shadow_ray;

	normal = intp.normal;

	if (shape->bump)
		normal = get_bump_normal(intp, shape);

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	inv_eye_dir = normalize_vec_inv(&eye_ray->direction);

	i = 0;
	while (i < scene->num_lights)
	{
		/* 入射ベクトル light_dir を計算する（点光源の場合と平行光源の場合） */
		light = &scene->lights[i];
		i++;

		if (light->type == LT_POINT || light->type == LT_SPOT)
			dir_pos_to_light = sub(&light->position, &intp.position);
		else
			dir_pos_to_light = normalize_vec_inv(&light->direction);	// 平行光源

		normalize(&dir_pos_to_light);
		nl_dot = CLAMP(dot(&normal, &dir_pos_to_light), 0, 1);
//		if (nl_dot <= 0 && shape->type == ST_PLANE)
//		{
//			normal = normalize_vec_inv(&normal);
//			nl_dot = CLAMP(dot(&normal, &dir_pos_to_light), 0, 1);
//		}

		/* shadow_rayを計算 */
		shadow_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &dir_pos_to_light);
		shadow_ray.direction = dir_pos_to_light;
		if (light->type == LT_POINT)
		{
			vec_pi_to_light = sub(&light->position, &intp.position);
			dist = norm(&vec_pi_to_light) - EPSILON;
		}
		else
			dist = FLT_MAX;

		shadow_int_res = get_nearest_shape(scene, &shadow_ray, dist, 1, NULL, NULL);

		/* shadow_rayが物体に遮られた場合 */
		if (shadow_int_res)
			continue ;

		/* shadow_rayが物体に遮られなかった場合 */

		/* checker */
		if (shape->type == ST_CORN || shape->type == ST_PLANE)
		{
			checker_col = get_checker_color(intp, shape);
			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&checker_col);
		}
//		checker_col = get_checker_color(intp, shape);
//		color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&checker_col);


		/* image texture */
		if (shape->texture)
		{
			img_col = get_img_color(intp, shape, *shape->texture);
			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&img_col);
		}

		if (light->type == LT_SPOT)
		{
			t_vector	light_to_pos = normalize_vec_inv(&dir_pos_to_light);
			float		alpha = acosf(dot(&light_to_pos, &light->direction));
			if (alpha > light->angle / 2.0f * (float)M_PI / 180.0f)
				continue ;

			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&light->illuminance);

			if (nl_dot <= 0.0f)
				continue ;

			/* 正反射ベクトルの計算 */
			ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos_to_light);
			normalize(&ref_dir);

			vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
			vr_dot_pow = powf(vr_dot, shape->material.shininess);

			/* 鏡面反射光の計算 */
			color = colorf_mul(&color, 1.0f, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
		}
		else
		{
			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&light->illuminance);

			/* 鏡面反射光 specular を計算してcolに足し合わせる */
			if (nl_dot <= 0.0f)
				continue ;

			/* 正反射ベクトルの計算 */
			ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos_to_light);
			normalize(&ref_dir);

			vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
			vr_dot_pow = powf(vr_dot, shape->material.shininess);

			/* 鏡面反射光の計算 */
			color = colorf_mul(&color, 1.0f, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
		}
	}
	return (color);
}
