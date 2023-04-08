/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/08 09:25:18 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 screen_x: [0, WIDTH)
 screen_y: [0, HEIGHT)
   v v v
 world_x: screen_x * u
 world_y: screen_y * v
 */

// ray_dir : camera_pos(x,y,z) -> screen(x,y,z)
t_vector	ray_dir(int i, int j, t_camera camera)
{
	t_vector	ray_dir;
	t_vector	screen_local;
	t_vector	screen_world;
	t_vector	screen_world_tmp;
	t_vector	screen_center;

	screen_local.x = (float)i + WINDOW_WIDTH / 2.0f;
	screen_local.y = 0.0f;
	screen_local.z = WINDOW_HEIGHT / 2.0f - (float)j;

	screen_world = Mv(camera.transpose_matrix_c2w, screen_local);
//	screen_world = add(&screen_center, &screen_world_tmp);
//	ray_dir = sub(&screen_world, &camera.pos);

	ray_dir = vec_calc(1.0f, &screen_world, camera.distance_camera_to_sc, &camera.dir_camera_to_sc_center);
	normalize(&ray_dir);
	return (ray_dir);

//	float screen_x = (float)x - (WINDOW_WIDTH - 1.0f) / 2.0f;
//	float screen_y = (WINDOW_HEIGHT - 1.0f) / 2.0f - (float)y;
//
//	t_vector	world_x = mult(screen_x, &camera.u);
//	t_vector	world_y = mult(screen_y, &camera.v);
//	t_vector	world_xyz = add(&world_x, &world_y);
//	t_vector	ray_dir = add(&camera.dir_camera_to_sc_center, &world_xyz);
//	normalize(&ray_dir);
//	return (ray_dir);
}
