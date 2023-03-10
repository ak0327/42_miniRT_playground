/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:32:22 by takira            #+#    #+#             */
/*   Updated: 2023/03/10 11:33:25 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	init_light(float x, float y, float z)
{
	t_light	light;

	light.vec_center.x = x;
	light.vec_center.y = y;
	light.vec_center.z = z;
	return (light);
}

int	diffuse_reflect(t_vector vec_screen, t_light light, t_sphere sphere)
{
	int		color;


	return (color);
}