/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/03/07 17:31:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	tr_screen_dimension_local_to_world(int x, int y, int w, int h)
{
	t_vector	vec;

	vec.x = (float)2 * (float)x / (float)(w - 1) - 1;
	vec.y = (float) -2 * (float)y / (float)(h - 1) + 1;
	vec.z = 0;
	return (vec);
}
