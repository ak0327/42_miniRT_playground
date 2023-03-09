/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:27 by takira            #+#    #+#             */
/*   Updated: 2023/03/08 20:11:02 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	init_sphere(float x, float y, float z, float r)
{
	t_sphere	sphere;

	sphere.cx = x;
	sphere.cy = y;
	sphere.cz = z;
	sphere.r = r;
	return (sphere);
}

/*
bool	is_intersect_to_sphere(t_sphere sphere, t_vector eye_vec, t_vector vec_screen)
{

	// D = B ** 2 -4 * A * C
	// if D < 0 return (false)
	return (true);
}*/