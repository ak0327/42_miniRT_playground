/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:20:47 by takira            #+#    #+#             */
/*   Updated: 2023/04/05 19:22:38 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	init_camera(void)
{
	t_camera	camera;
	float		theta_radians;
	float		distance_camera_to_screen;
	float		unit;

//	SET_VECTOR(camera.center, 0.0f, 5.0f, -10.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.2f, 1.0f)

//	SET_VECTOR(camera.center, 0.0f, 0.0f, 0.0f)
//	SET_VECTOR(camera.dir, 0.0f, 0.0f, 1.0f)

/* corn */
//	SET_VECTOR(camera.center, 5.0f, 25.0f, -50.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.3f, 1.0f)

/* spot */
//	SET_VECTOR(camera.center, 0.0f, 25.0f, -60.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.3f, 1.0f)

/* bump */
	SET_VECTOR(camera.center, 0.0f, 100.0f, -60.0f)
	SET_VECTOR(camera.dir, 0.0f, -1.0f, 1.0f)


	normalize(&camera.dir);
	camera.fov_deg = 60.0f;

	theta_radians  = camera.fov_deg * (float)M_PI / 180.0f;
	distance_camera_to_screen = WINDOW_HEIGHT * ASPECT / 2.0f / tanf(theta_radians / 2.0f);

	normalize(&camera.dir);
	camera.dir_camera_to_sc_center = mult(distance_camera_to_screen, &camera.dir);

	camera.u.x = camera.dir_camera_to_sc_center.z / sqrtf(SQR(camera.dir_camera_to_sc_center.x) + SQR(camera.dir_camera_to_sc_center.z));
	camera.u.y = 0.0f;
	camera.u.z = -1.0f * camera.dir_camera_to_sc_center.x / sqrtf(SQR(camera.dir_camera_to_sc_center.x) + SQR(camera.dir_camera_to_sc_center.z));
	normalize(&camera.u);

	camera.v = cross(&camera.dir_camera_to_sc_center, &camera.u);
	normalize(&camera.v);

	if (camera.dir.x == 0.0f && camera.dir.y != 0.0f && camera.dir.z == 0.0f)
	{
		if (camera.dir.y > 0.0f)
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
	return (camera);
}