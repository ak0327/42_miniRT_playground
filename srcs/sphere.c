/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:27 by takira            #+#    #+#             */
/*   Updated: 2023/03/10 20:05:07 by takira           ###   ########.fr       */
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

float	discriminant(t_sphere sphere, t_vector vec_eye, t_vector vec_screen, float *t)
{
	float		A, B, C, D;
	float		t1, t2;
	t_vector	directional_vec_eye;
	t_vector	vec_pi;

	*t = 0;
	directional_vec_eye = sub(&vec_screen, &vec_eye);
	vec_pi = sub(&sphere.vec_center, &vec_eye);
	A = squared_norm(&directional_vec_eye);
	B = 2 * dot(&directional_vec_eye, &vec_pi);
	C = squared_norm(&vec_pi) - SQR(sphere.radius);
	D = SQR(B) - 4 * A * C;
	if (D == 0)
		*t = (-B + sqrtf(D)) / (2 * A);
	if (D > 0)
	{
		t1 = (-B + sqrtf(D)) / (2 * A);
		t2 = (-B - sqrtf(D)) / (2 * A);
		if (t1 > 0 && t2 > 0)
			*t = MIN(t1, t2);
	}
	return (D);
}

//TODO; tの判定
bool	is_intersect_to_sphere(t_sphere sphere, t_vector vec_eye, t_vector vec_screen, float *t)
{
	float	D;

	D = discriminant(sphere, vec_eye, vec_screen, t);
	if (D < 0 || t <= 0)
		return (false);

	return (true);
}
