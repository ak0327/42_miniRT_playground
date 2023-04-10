/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:12:18 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 13:56:42 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_dir_pos2light(t_light light, t_vector pos)
{
	t_vector	dir_pos2light;

	if (light.type == LT_POINT || light.type == LT_SPOT)
		dir_pos2light = sub(&light.position, &pos);
	else
		dir_pos2light = normalize_vec_inv(&light.direction);	// 平行光源
	dir_pos2light = normalize_vec(&dir_pos2light);
	return (dir_pos2light);
}

int is_obj_exists_between_light_and_eye(const t_scene *scene, t_vector dir_pos2light, t_light *light, t_intersection_point intp)
{
	int 		shadow_intersect_result;
	t_ray		shadow_ray;
	t_vector	vec_pi_to_light;
	float		dist;

	/* shadow_rayを計算 */
	shadow_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &dir_pos2light);
	shadow_ray.direction = dir_pos2light;
	if (light->type == LT_POINT)
	{
		vec_pi_to_light = sub(&light->position, &intp.position);
		dist = norm(&vec_pi_to_light) - EPSILON;
	}
	else
		dist = FLT_MAX;
	shadow_intersect_result = get_nearest_shape(scene, &shadow_ray, dist, 1, NULL, NULL);
	return (shadow_intersect_result);
}

t_colorf calc_diffuse_reflection(const t_scene *scene, const t_ray *eye_ray,
						  t_intersection_point intp, t_shape *shape)
{
	t_colorf	color, checker_col, img_col;
	size_t		i;
	t_light		*light;
	t_vector	ref_dir, dir_pos2light, inv_eye_dir, normal;
	float		nl_dot, vr_dot, vr_dot_pow;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	normal = intp.normal;
	if (shape->material.bump.data)
		normal = get_bump_normal(intp, shape);

	inv_eye_dir = normalize_vec_inv(&eye_ray->direction);

	i = 0;
	while (i < scene->num_lights)
	{
		light = &scene->lights[i];
		i++;

		dir_pos2light = get_dir_pos2light(*light, intp.position);
		nl_dot = CLAMP(dot(&normal, &dir_pos2light), 0, 1);

		if (is_obj_exists_between_light_and_eye(scene, dir_pos2light, light, intp))
			continue ;

		/* checker */
		if (shape->material.is_checker)
		{
			checker_col = get_checker_color(intp, shape);
			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&checker_col);
		}

		/* image texture */
		if (shape->material.texture.data)
		{
			img_col = get_img_color(intp, shape, shape->material.texture);
			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&img_col);
		}

		if (light->type == LT_SPOT)
		{
			t_vector	light_to_pos = normalize_vec_inv(&dir_pos2light);
			float		alpha = acosf(dot(&light_to_pos, &light->direction));
			if (alpha > light->angle / 2.0f * (float)M_PI / 180.0f)
				continue ;

			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&light->illuminance);

			if (nl_dot <= 0.0f)
				continue ;

			/* 正反射ベクトルの計算 */
			ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos2light);
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
			ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos2light);
			normalize(&ref_dir);

			vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
			vr_dot_pow = powf(vr_dot, shape->material.shininess);

			/* 鏡面反射光の計算 */
			color = colorf_mul(&color, 1.0f, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
		}
	}
	return (color);
}
