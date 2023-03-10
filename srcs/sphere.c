/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:27 by takira            #+#    #+#             */
/*   Updated: 2023/03/09 11:56:55 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	init_sphere(float x, float y, float z, float r)
{
	t_sphere	sphere;

	sphere.radius = r;
	sphere.vec_center = init_vector(x, y, z);
//	printf("sphere vec_c:%s, sqn:%f\n", vector_str(&sphere.vec_center), squared_norm(&sphere.vec_center));
	return (sphere);
}

float	discriminant(t_sphere sphere, t_vector vec_eye, t_vector vec_screen)
{
	float		A, B, C, D;
	t_vector	d_vec_eye;
	t_vector	vec_sc;

	d_vec_eye = sub(&vec_screen, &vec_eye);
	vec_sc = sub(&sphere.vec_center, &vec_eye);
	A = squared_norm(&d_vec_eye);
	B = 2 * dot(&d_vec_eye, &vec_sc);
	C = squared_norm(&vec_sc) - SQR(sphere.radius);
	D = SQR(B) - 4 * A * C;
	return (D);
}

//TODO; tの判定
bool	is_intersect_to_sphere(t_sphere sphere, t_vector vec_eye, t_vector vec_screen)
{
	if (discriminant(sphere, vec_eye, vec_screen) < 0)
		return (false);

	return (true);
}
