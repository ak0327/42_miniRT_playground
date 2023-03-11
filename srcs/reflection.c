/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:32:22 by takira            #+#    #+#             */
/*   Updated: 2023/03/10 11:33:25 by takira           ###   ########.fr       */
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
	int		color;
	t_vector	directional_vec_eye;
	t_vector	vec_pi;
	t_vector	vec_center_to_pi;
	t_vector	unit_normal_vec_pi;

	directional_vec_eye = sub(&vec_screen, &vec_eye);
	directional_vec_eye = mult(t, &directional_vec_eye);
	vec_pi = add(&vec_eye, &directional_vec_eye);
	vec_center_to_pi = sub(&vec_pi, &sphere.vec_center);
	unit_normal_vec_pi = mult(1 / normalize(&vec_center_to_pi), &vec_center_to_pi);

	return (color);
}