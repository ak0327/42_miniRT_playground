/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:20:47 by takira            #+#    #+#             */
/*   Updated: 2023/03/19 12:20:59 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	init_camera(void)
{
	t_camera	camera;
	float		theta_radians;
	float		distance_camera_to_screen;

	SET_VECTOR(camera.center, 0.0f, 5.0f, -10.0f)
	SET_VECTOR(camera.dir, 0.0f, -0.2f, 1.0f)
	normalize(&camera.dir);
	camera.fov_deg = 70;

	theta_radians  = camera.fov_deg * (float)M_PI / 180.0f;
	distance_camera_to_screen = WINDOW_WIDTH / 2.0f / tanf(theta_radians / 2);

	normalize(&camera.dir);
	camera.dir_camera_to_sc_center = mult(distance_camera_to_screen, &camera.dir);

	camera.u.x = camera.dir_camera_to_sc_center.z / sqrtf(SQR(camera.dir_camera_to_sc_center.x) + SQR(camera.dir_camera_to_sc_center.z));
	camera.u.y = 0;
	camera.u.z = -1 * camera.dir_camera_to_sc_center.x / sqrtf(SQR(camera.dir_camera_to_sc_center.x) + SQR(camera.dir_camera_to_sc_center.z));
	normalize(&camera.u);

	camera.v = mult(-1, &camera.dir_camera_to_sc_center);
	camera.v = cross(&camera.u, &camera.v);
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
	return (camera);
}