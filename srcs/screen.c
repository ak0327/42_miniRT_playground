/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/03/09 10:42:37 by takira           ###   ########.fr       */
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
