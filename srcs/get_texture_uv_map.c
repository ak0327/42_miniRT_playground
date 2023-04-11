/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:02:49 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 10:27:18 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//t_texture_map	get_cylindrical_map(t_vector pos_local, t_matrix Tr, float h)
//{
//	t_vector		pos_uv;
//	t_texture_map	map;
//	float			phi;
//	float			shift = (float)M_PI;
//
//	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)
//	phi = atan2f(pos_uv.z, pos_uv.x);
//	map.u = (phi + (float)M_PI + shift) / (2.0f * (float)M_PI);
//	map.v = pos_uv.y / h;
//	return (map);
//}

//t_texture_map	get_conical_map(t_vector pos_local, t_matrix Tr, float h)
//{
//	t_vector		pos_uv;
//	t_texture_map	map;
//	float			phi;
//	float			shift = (float)M_PI;
//
//	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)
//	phi = atan2f(pos_uv.z, pos_uv.x);
//	map.u = (phi + (float)M_PI + shift) / (2.0f * (float)M_PI);
//	map.v = pos_uv.y / h;
//	return (map);
//}

//t_texture_map	get_planar_map(t_vector pos_local, t_matrix Tr)
//{
//	t_vector		pos_uv;
//	t_texture_map	map;
//
//	pos_uv = mul_matrix_vec(Tr, pos_local);	// pos(x,y,z)->pos(u,v,w)
//	map.u = pos_uv.x;
//	map.v = pos_uv.z;
//	return (map);
//}


//t_texture_map	get_spherical_map(t_vector pos_local)
//{
//	t_texture_map	map;
//	float			radius;
//	float			theta;
//	float			phi;
//	float			shift = (float)M_PI;
//
//	radius = norm(&pos_local);
//	theta = acosf(pos_local.y / radius);
//	phi = atan2f(pos_local.z, pos_local.x);
//
//	map.u = (phi + (float)M_PI + shift) / (2.0f * (float)M_PI);		// 0 <= fu <= 1
//	map.v = theta / (float)M_PI;	// 0 <= fv <= 1
//	return (map);
//}


t_texture_map	get_planar_map(t_vector int_pos, t_vector center_pos, t_vector obj_normal)
{
	t_vector		pos_uv;
	t_texture_map	map;
	t_vector		pos_local;
	t_matrix		Tr_matrix_world2obj;

	pos_local = sub(&int_pos, &center_pos);
	Tr_matrix_world2obj = get_tr_matrix_world2obj_yup(obj_normal);

	pos_uv = mul_matrix_vec(Tr_matrix_world2obj, pos_local);	// pos(x,y,z)->pos(u,v,w)
	map.u = pos_uv.x;
	map.v = pos_uv.z;
	return (map);
}


t_texture_map	get_spherical_map(t_vector int_pos, t_vector center_pos, float obj_radius)
{
	t_texture_map	map;
	float			theta;
	float			phi;
	t_vector		pos_local;

	pos_local = sub(&int_pos, &center_pos);
	theta = acosf(pos_local.y / obj_radius);
	phi = atan2f(pos_local.z, pos_local.x);[]

	map.u = (phi + (float)M_PI) / (2.0f * (float)M_PI);		// 0 <= u <= 1
	map.v = theta / (float)M_PI;							// 0 <= v <= 1
	return (map);
}

t_texture_map	get_cylindrical_map(t_vector int_pos, t_vector center_pos, t_vector obj_dir, float obj_height)
{
	t_vector		pos_uv;
	t_vector		pos_local;
	t_matrix		Tr_matrix_world2obj;
	t_texture_map	map;
	float			phi;

	pos_local = sub(&int_pos, &center_pos);
	Tr_matrix_world2obj = get_tr_matrix_world2obj_zup(obj_dir);
	pos_uv = mul_matrix_vec(Tr_matrix_world2obj, pos_local);	// pos(x,y,z)->pos(u,v,w)
	phi = atan2f(pos_uv.z, pos_uv.x);
	map.u = (phi + (float)M_PI) / (2.0f * (float)M_PI);		// 0 <= u <= 1
	map.v = pos_uv.y / obj_height;
	return (map);
}

t_texture_map	get_conical_map(t_vector int_pos, t_vector center_pos, t_vector obj_dir, float obj_height)
{
	t_vector		pos_uv;
	t_vector		pos_local;
	t_matrix		Tr_matrix_world2obj;
	t_texture_map	map;
	float			phi;

	pos_local = sub(&int_pos, &center_pos);
	Tr_matrix_world2obj = get_tr_matrix_world2obj_zup(obj_dir);
	pos_uv = mul_matrix_vec(Tr_matrix_world2obj, pos_local);	// pos(x,y,z)->pos(u,v,w)
	phi = atan2f(pos_uv.z, pos_uv.x);
	map.u = (phi + (float)M_PI) / (2.0f * (float)M_PI);		// 0 <= u <= 1
	map.v = pos_uv.y / obj_height;
	return (map);
}
