/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/07 20:49:51 by takira           ###   ########.fr       */
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
t_vector	ray_dir(int x, int y, t_camera camera)
{
//	t_vector	ray_dir;
//
//	float	screen_u, screen_v, screen_w;
//	screen_u = (float)x + WINDOW_WIDTH / 2.0f;
//	screen_v = (float)y
//
//	return (ray_dir);




	float screen_x = (float)x - (WINDOW_WIDTH - 1.0f) / 2.0f;
	float screen_y = (WINDOW_HEIGHT - 1.0f) / 2.0f - (float)y;

	t_vector	world_x = mult(screen_x, &camera.u);
	t_vector	world_y = mult(screen_y, &camera.v);
	t_vector	world_xyz = add(&world_x, &world_y);
	t_vector	ray_dir = add(&camera.dir_camera_to_sc_center, &world_xyz);
	normalize(&ray_dir);
	return (ray_dir);
}
