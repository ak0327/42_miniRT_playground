/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/03/21 17:10:10 by takira           ###   ########.fr       */
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

t_vector	ray_dir(int x, int y, t_camera camera)
{
	float screen_x = (float)x - (WINDOW_WIDTH - 1.0f) / 2.0f;
	float screen_y = (WINDOW_HEIGHT - 1.0f) / 2.0f - (float)y;

	t_vector	world_x = mult(screen_x, &camera.u);
	t_vector	world_y = mult(screen_y, &camera.v);

	t_vector ray_dir = add(&world_x, &world_y);
	ray_dir = add(&camera.dir_camera_to_sc_center, &ray_dir);
	normalize(&ray_dir);
	return (ray_dir);
}
