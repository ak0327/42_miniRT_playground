/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 17:28:58 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{

}

int intersection_test(const t_shape *shape, const t_ray * ray, t_intersection_point * out_intp)
{

}

int get_nearest_shape(const t_scene *scene, const t_ray *ray, float max_dist, int exit_once_found,
					  t_shape **out_shape, t_intersection_point *out_intp)
{

}