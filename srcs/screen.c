/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/03/20 13:48:17 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	tr_screen_dimension_local_to_world(int x, int y)
{
	t_vector	vec;
	float		screen_w = 2;
	float		screen_h = 2;
	float		window_w = 512;
	float		window_h = 512;

	vec.x = screen_w * (float)x / (window_w - 1) - 1;
	vec.y = -screen_h * (float)y / (window_h - 1) + 1;
	vec.z = 0;
	return (vec);
}

t_vector	camera(int x, int y, t_vector lookfrom, t_vector lookat, float fov)
{
	t_vector	vup = init_vector(0.0f, 0.1f, 0.0f);
	t_vector	vec;

	t_vector	u, v, w;
	w = sub(&lookfrom, &lookat);
	normalize(&w);

	u = cross(&vup, &w);
	normalize(&u);

	v = cross(&w, &u);
	normalize(&v);

	float	aspect_ratio = 1.0f;
	float	thata_radians = fov * (float)M_PI / 180;
	float	h = tanf(thata_radians / 2);
	float	viewpoint_height = 2.0f * h;
	float	viewpoint_width = aspect_ratio * viewpoint_height;

	t_vector	origin = lookfrom;
	t_vector	horizontal = mult(viewpoint_width, &u);
	t_vector	vertical = mult(viewpoint_height, &w);


	return (vec);
}

t_vector	ray_dir(int x, int y, t_camera camera)
{
	/* camera */
	const float	window_w = 512.0f;
	const float	window_h = 512.0f;
	float		theta_radians = camera.fov_deg * (float)M_PI / 180.0f;
	float		distance_camera_to_screen = window_w / 2.0f / tanf(theta_radians / 2);
	normalize(&camera.dir);
	t_vector	dir_camera_to_sc_center = mult(distance_camera_to_screen, &camera.dir);

	camera.u.x = dir_camera_to_sc_center.z / sqrtf(SQR(dir_camera_to_sc_center.x) + SQR(dir_camera_to_sc_center.z));
	camera.u.y = 0;
	camera.u.z = -1 * dir_camera_to_sc_center.x / sqrtf(SQR(dir_camera_to_sc_center.x) + SQR(dir_camera_to_sc_center.z));
	normalize(&camera.u);

	camera.v = mult(-1, &dir_camera_to_sc_center);
	camera.v = cross(&camera.u, &camera.v);
//	camera.v = cross(&camera.u, &dir_camera_to_sc_center);

	normalize(&camera.v);

	if (camera.dir.x == 0 && camera.dir.y != 0 && camera.dir.z == 0)
	{
		if (camera.dir.y > 0)
		{
			SET_VECTOR(camera.u, -1.0f, 0.0f, 0.0f)
			SET_VECTOR(camera.v, 0.0f, 0.0f, -1.0f)
		}
		else
		{
			SET_VECTOR(camera.u, 1.0f, 0.0f, 0.0f)
			SET_VECTOR(camera.v, 0.0f, 0.0f, 1.0f)
		}
	}

	/* screen */
	float sw = (float)x - (window_w - 1.0f) / 2.0f;
	float sh = (window_h - 1.0f) / 2.0f - (float)y;

	t_vector	xx = mult(sw, &camera.u);
	t_vector	yy = mult(sh, &camera.v);

//	t_vector	P_sc = vec_calc((float)x - (window_w - 1.0f) / 2.0f, &u, (window_h - 1.0f) / 2.0f - (float)y, &v);
	t_vector ray_dir = add(&xx, &yy);
	ray_dir = add(&dir_camera_to_sc_center, &ray_dir);
//	ray_dir = add(&camera_dir, &P_sc);
	normalize(&ray_dir);
	return (ray_dir);
}

// 0<=x<W, 0<=y<=H -> world(x,y,z)
t_vector	get_camera_to_screen_vec(int x, int y, t_vector camera_center, t_vector camera_dir, float fov)
{
	t_vector	vec_screen;
	t_vector	sc_u;
	t_vector	sc_v;
	t_vector	camera_to_sc_c;

	float		d_camera_to_screen;

	float		window_w = 512.0f;
	float		window_h = 512.0f;

	d_camera_to_screen = window_w / 2.0f / (tanf(fov / 2 * (float)M_PI / 180.0f));
	camera_to_sc_c = vec_calc(1, &camera_center, d_camera_to_screen, &camera_dir);

	sc_u.x = -1 * camera_to_sc_c.y / sqrtf(SQR(camera_to_sc_c.x) + SQR(camera_to_sc_c.y));
	sc_u.y = camera_to_sc_c.x / sqrtf(SQR(camera_to_sc_c.x) + SQR(camera_to_sc_c.y));
	sc_u.z = 0;
	sc_v = cross(&camera_to_sc_c, &sc_u);

	vec_screen = vec_calc(((float)x - window_w / 2), &sc_u, -1 * ((float)y - window_h / 2), &sc_v);
	vec_screen = add(&camera_to_sc_c, &vec_screen);
	return (vec_screen);
}