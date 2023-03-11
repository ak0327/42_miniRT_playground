/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:32:22 by takira            #+#    #+#             */
/*   Updated: 2023/03/11 16:02:27 by takira           ###   ########.fr       */
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
	t_vector	directional_vec_eye;
	t_vector	vec_eye_to_pi;
	t_vector	vec_pi;
	t_vector	vec_center_to_pi;
	t_vector	vec_pi_to_light;
	float		nl;

	directional_vec_eye = sub(&vec_screen, &vec_eye);
	vec_eye_to_pi = mult(t, &directional_vec_eye);

	vec_pi = add(&vec_eye, &vec_eye_to_pi);
	vec_center_to_pi = sub(&vec_pi, &sphere.vec_center);
	normalize(&vec_center_to_pi);

	vec_pi_to_light = sub(&light.vec_center, &vec_pi);
	normalize(&vec_pi_to_light);

	printf("nl:%f\n", dot(&vec_center_to_pi, &vec_pi_to_light));
	nl = MIN(1, dot(&vec_center_to_pi, &vec_pi_to_light));
	nl = MAX(0, nl);
	r_diffuse = (int)(255 * nl);
	color = r_diffuse << 16 | r_diffuse << 8 | r_diffuse;
//	printf("color:%#X, nl:%f\n", color, nl);
	return (color);
}
