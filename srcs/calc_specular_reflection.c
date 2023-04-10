/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:12:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 16:20:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	get_specular_reflection_color(t_shape *shape, float nl_dot, t_light *light, t_vector dir_pos2light, t_vector eye_dir)
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

	ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos2light);
	normalize(&ref_dir);

	vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);

	if (vr_dot <= 0.0f)
		return (color);

	vr_dot_pow = powf(vr_dot, shape->material.shininess);

	color = colorf_mul_k1c1k2c2(&color, 1.0f, &shape->material.specular_ref,
								vr_dot_pow, &light->illuminance);
	return (color);
}

t_colorf calc_specular_reflection(const t_scene *scene, const t_ray *eye_ray,
								  t_intersection_point intp, t_shape *shape)
{
	t_colorf	color;
	size_t		idx;
	t_light		*light;
	t_vector	dir_pos2light, normal;
	float		nl_dot;
	t_colorf	color_specular_ref;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	normal = intp.normal;
	if (shape->material.bump.data)
		normal = get_bump_normal(intp, shape);

	idx = 0;
	while (idx < scene->num_lights)
	{
		light = &scene->lights[idx];
		idx++;

		dir_pos2light = get_dir_pos2light(*light, intp.position);
		nl_dot = CLAMP(dot(&normal, &dir_pos2light), 0, 1); // n*l <= 0 -> color = 0になる

		if (is_obj_exists_between_light_and_eye(scene, dir_pos2light, light, intp))
			continue ;

		if (nl_dot <= 0.0f)
			continue ;

		color_specular_ref = get_specular_reflection_color(shape, nl_dot, light, dir_pos2light, eye_ray->direction);
		color = colorf_add(color, color_specular_ref);
	}
	return (color);
}
