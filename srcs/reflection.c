/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:32:22 by takira            #+#    #+#             */
/*   Updated: 2023/03/11 16:43:27 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	init_light(float x, float y, float z)
{
	t_light	light;

	light.vec_center.x = x;
	light.vec_center.y = y;
	light.vec_center.z = z;
	return (light);
}

int	diffuse_reflect(t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t)
{
	int			r_diffuse;
	int			color;
	t_vector	vec_eye_to_screen;
	t_vector	vec_eye_to_pi;
	t_vector	vec_pi;

	t_vector	vec_sphere_n;
	t_vector	vec_light_dir;
	float		nl_dot;

	vec_eye_to_screen = sub(&vec_screen, &vec_eye);
	vec_eye_to_pi = mult(t, &vec_eye_to_screen);
	vec_pi = add(&vec_eye, &vec_eye_to_pi);
	vec_sphere_n = sub(&vec_pi, &sphere.vec_center);
	normalize(&vec_sphere_n);

	vec_light_dir = sub(&light.vec_center, &vec_pi);
	normalize(&vec_light_dir);
//	printf("vec_center->pi:%s, vec_pi->light:%s\n", \
//	vector_str(&vec_sphere_n), vector_str(&vec_light_dir));

//	printf("nl_dot:%f\n", dot(&vec_sphere_n, &vec_light_dir));
	nl_dot = dot(&vec_sphere_n, &vec_light_dir);
	nl_dot = CLAMP(nl_dot, 0, 1);

	r_diffuse = (int)(255 * nl_dot);
	color = r_diffuse << 16 | r_diffuse << 8 | r_diffuse;
//	printf("color:%#X, nl_dot:%f\n", color, nl_dot);
	return (color);
}
