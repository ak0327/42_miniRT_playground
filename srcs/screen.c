/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/01 12:17:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	tr_screen_dimension_local_to_world(int x, int y)
{
	t_vector	vec;
	float		screen_w = 2.0f;
	float		screen_h = 2.0f;

	vec.x = screen_w * (float)x / (WINDOW_WIDTH - 1.0f);
	vec.y = 1.0f - screen_h * (float)y / (WINDOW_HEIGHT - 1.0f);
	vec.z = 0.0f;
	return (vec);
}

t_vector	ray_dir(int x, int y, t_camera camera)
{
	float screen_y = (WINDOW_HEIGHT - 1.0f) / 2.0f - (float)y;
	float screen_x = (float)x - (WINDOW_HEIGHT * ASPECT- 1.0f) / 2.0f;

	t_vector	world_x = mult(screen_x, &camera.u);
	t_vector	world_y = mult(screen_y, &camera.v);

	t_vector ray_dir = add(&world_x, &world_y);
	ray_dir = add(&camera.dir_camera_to_sc_center, &ray_dir);
	normalize(&ray_dir);
	return (ray_dir);
}
