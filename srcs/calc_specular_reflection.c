/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:12:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 14:39:03 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	calc_specular_reflection(t_shape *shape, float nl_dot, t_light *light, t_vector dir_pos2light, t_vector eye_dir)
{
	t_colorf	color;
	t_vector	ref_dir, inv_eye_dir, normal;
	float		vr_dot, vr_dot_pow;
	t_vector	light_to_pos;
	float		alpha;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	inv_eye_dir = normalize_vec_inv(&eye_dir);

	if (light->type == LT_SPOT)
	{
		light_to_pos = normalize_vec_inv(&dir_pos2light);
		alpha = acosf(dot(&light_to_pos, &light->direction));

		if (alpha > light->angle / 2.0f * (float)M_PI / 180.0f)
			return (color);
	}

	if (nl_dot <= 0.0f)
		return (color);

	ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos2light);
	normalize(&ref_dir);

	vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
	vr_dot_pow = powf(vr_dot, shape->material.shininess);

	color = colorf_mul(&color, 1.0f, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
	return (color);
}