/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:32:22 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 11:32:07 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	init_light(float x, float y, float z)
{
	t_light	light;

	light.vector.x = x;
	light.vector.y = y;
	light.vector.z = z;
	return (light);
}

float	calc_nl_dot(t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t)
{
	t_vector	vec_eye_to_screen;
	t_vector	vec_eye_to_pi;
	t_vector	vec_pi;

	t_vector	vec_sphere_n;
	t_vector	vec_light_dir;

	vec_eye_to_screen = sub(&vec_screen, &vec_eye);
	vec_eye_to_pi = mult(t, &vec_eye_to_screen);
	vec_pi = add(&vec_eye, &vec_eye_to_pi);
	vec_sphere_n = sub(&vec_pi, &sphere.vec_center);
	normalize(&vec_sphere_n);

	vec_light_dir = sub(&light.vector, &vec_pi);
	normalize(&vec_light_dir);

	return (CLAMP(dot(&vec_sphere_n, &vec_light_dir), 0, 1));
}

float	diffuse(float nl_dot)
{
	const float	kd = 0.69f;
	const float	Ii = 1.0f;
	float		r_diffuse;

	r_diffuse = kd * Ii * nl_dot;
	return (r_diffuse);
}

float	ambient(void)
{
	const float	ka = 0.01f;
	const float	Ia = 0.1f;
	return (ka * Ia);
}

float	specular(float nl_dot, t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t)
{
	const float	ks = 0.3f;
	const float	alpha = 8.0f;
	const float	Ii = 1.0f;

	if (nl_dot <= 0)
		return (0);

	t_vector	vec_eye_to_screen;
	t_vector	vec_eye_to_pi;
	t_vector	vec_pi;

	t_vector	vec_sphere_n;
	t_vector	vec_light_dir;

	t_vector	vec_r;
	t_vector	vec_r_tmp;
	t_vector	vec_v;

	float		vr_dot;
	float		r_specular;

	vec_eye_to_screen = sub(&vec_screen, &vec_eye);
	vec_eye_to_pi = mult(t, &vec_eye_to_screen);
	vec_pi = add(&vec_eye, &vec_eye_to_pi);
	vec_sphere_n = sub(&vec_pi, &sphere.vec_center);
	normalize(&vec_sphere_n);

	vec_light_dir = sub(&light.vector, &vec_pi);
	normalize(&vec_light_dir);

	vec_r_tmp = mult(2 * nl_dot, &vec_sphere_n);
	vec_r = sub(&vec_r_tmp, &vec_light_dir);
	normalize(&vec_r);
	vec_v = mult(-1, &vec_eye_to_screen);
	normalize(&vec_v);

	vr_dot = CLAMP(dot(&vec_v, &vec_r), 0, 1);
	r_specular = ks * Ii * powf(vr_dot, alpha);
	return (r_specular);
}

int	shading(t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t)
{
	int		color;
	float	r_diffuse;
	float	r_ambient;
	float	r_specular;
	float	r_luminance;
	float	nl_dot;

	nl_dot = calc_nl_dot(vec_eye, vec_screen, light, sphere, t);

	r_diffuse = diffuse(nl_dot);
	r_ambient = ambient();
	r_specular = specular(nl_dot, vec_eye, vec_screen, light, sphere, t);
	r_luminance = r_diffuse + r_ambient + r_specular;
	r_luminance = 256 * CLAMP(r_luminance, 0, 1);
	color = (int)(r_luminance) << 16 | (int)(r_luminance) << 8 | (int)(r_luminance);
	return (color);

}
























