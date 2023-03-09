/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:27 by takira            #+#    #+#             */
/*   Updated: 2023/03/09 11:53:54 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	init_sphere(float x, float y, float z, float r)
{
	t_sphere	sphere;

	sphere.cx = x;
	sphere.cy = y;
	sphere.cz = z;
	sphere.r = r;
	sphere.vev_c = init_vector(x, y, z);
//	printf("sphere vec_c:%s, sqn:%f\n", vector_str(&sphere.vev_c), squared_norm(&sphere.vev_c));
	return (sphere);
}

float	discriminant(t_sphere sphere, t_vector vec_eye, t_vector vec_screen)
{
	float		a;
	float		b;
	float		c;
	t_vector	d_vec_eye;
	t_vector	vec_sc;
	float		ans;

	d_vec_eye = sub(&vec_screen, &vec_eye);
	vec_sc = sub(&sphere.vev_c, &vec_eye);
	a = squared_norm(&d_vec_eye);
	b = 2 * dot(&d_vec_eye, &vec_sc);
	c = squared_norm(&vec_sc) - sphere.r * sphere.r;
	ans = b * b - 4 * a * c;
//	printf("a:%f, b:%f, c:%f -> ans:%f\n", a, b, c, ans);
	return (ans);
}

//TODO; tの判定
bool	is_intersect_to_sphere(t_sphere sphere, t_vector vec_eye, t_vector vec_screen)
{
//	t_vector	directional_vec;

//	directional_vec = sub(&vec_screen, &vec_eye);
	if (discriminant(sphere, vec_eye, vec_screen) < 0)
		return (false);

	return (true);
}
