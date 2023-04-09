/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:02:49 by takira            #+#    #+#             */
/*   Updated: 2023/04/09 19:43:04 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_texture_map	get_cylindrical_map(t_vector pos_local, t_matrix Tr, float h)
{
	t_vector		pos_uv;
	t_texture_map	map;
	float			phi;

	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)
	phi = atan2f(pos_uv.z, pos_uv.x);
	map.u = (phi + (float)M_PI) / (2.0f * (float)M_PI);
	map.v = pos_uv.y / h;
	return (map);
}

t_texture_map	get_conical_map(t_vector pos_local, t_matrix Tr, float h)
{
	t_vector		pos_uv;
	t_texture_map	map;
	float			phi;

	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)
	phi = atan2f(pos_uv.z, pos_uv.x);
	map.u = (phi + (float)M_PI) / (2.0f * (float)M_PI);
	map.v = pos_uv.y / h;
	return (map);
}

t_texture_map	get_planar_map(t_vector pos_local, t_matrix Tr)
{
	t_vector		pos_uv;
	t_texture_map	map;

	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)
	map.u = pos_uv.x;
	map.v = pos_uv.z;
	return (map);
}

t_texture_map	get_spherical_map(t_vector pos_local)
{
	t_texture_map	map;
	float			radius;
	float			theta;
	float			phi;

	radius = norm(&pos_local);
	theta = acosf(pos_local.y / radius);
	phi = atan2f(pos_local.z, pos_local.x);

	map.u = (phi + (float)M_PI) / (2.0f * (float)M_PI);		// 0 <= fu <= 1
	map.v = theta / (float)M_PI;	// 0 <= fv <= 1
	return (map);
}