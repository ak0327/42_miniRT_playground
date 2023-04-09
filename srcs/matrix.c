/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:50:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/09 14:02:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	get_tr_matrix_world2tangent(t_vector w_dir)
{
	t_vector	eu, ew, ev;
	t_vector	ex, ey, ez;
	t_matrix	Tr;

	SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
	SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
	SET_VECTOR(ez, 0.0f, 0.0f, 1.0f);

	ev = w_dir;
	eu = cross(&ev, &ey);
	ew = cross(&eu, &ev);

	if (ev.x == ey.x && ev.y == ey.y && ev.z == ey.z)
	{
		eu = ex;
		ew = ez;
	}
	if (ev.x == ey.x && ev.y == -ey.y && ev.z == ey.z)
	{
		eu = normalize_vec_inv(&ex);
		ew = normalize_vec_inv(&ez);
	}
	Tr = set_matrix(eu, ev, ew);
	return(Tr);
}

t_matrix	get_tr_matrix_world2obj_yup(t_vector w_dir)
{
	t_vector	eu, ew, ev;
	t_vector	ex, ey, ez;
	t_matrix	Tr;

	SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
	SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
	SET_VECTOR(ez, 0.0f, 0.0f, 1.0f);

	ev = w_dir;
	eu = cross(&ev, &ey);
	ew = cross(&eu, &ev);

	if (ev.x == ey.x && ev.y == ey.y && ev.z == ey.z)
	{
		eu = ex;
		ew = ez;
	}
	if (ev.x == ey.x && ev.y == -ey.y && ev.z == ey.z)
	{
		eu = ex;
		ew = normalize_vec_inv(&ez);
	}

	Tr = set_matrix(eu, ev, ew);	// (x,y,z)->(u,w,v)への変換matrix
	return (Tr);
}

t_matrix	get_tr_matrix_world2obj_zup(t_vector w_dir)
{
	t_vector	eu, ew, ev;
	t_vector	ex, ey, ez;
	t_matrix	Tr;

	SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
	SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
	SET_VECTOR(ez, 0.0f, 0.0f, 1.0f);

	ev = normalize_vec(&w_dir);
	eu = cross(&ev, &ez);
	ew = cross(&eu, &ev);
	if (ev.x == ez.x && ev.y == ez.y && ev.z == ez.z)
	{
		eu = ex;
		ew = normalize_vec_inv(&ey);
	}
	if (ev.x == ez.x && ev.y == ez.y && ev.z == -ez.z)
	{
		eu = ex;
		ew = ey;
	}
	// こっちでもOK
//	ew = cross(&ex, &ev);
//	eu = cross(&ev, &ew);
//	if (ev.x == ex.x && ev.y == ex.y && ev.z == ex.z)
//	{
//		eu = normalize_vec_inv(&ey);
//		ew = ez;
//	}
//	if (ev.x == -ex.x && ev.y == ex.y && ev.z == ex.z)
//	{
//		eu = ey;
//		ew = ez;
//	}
	Tr = set_matrix(eu, ev, ew);	// (x,y,z)->(u,v,w)への変換matrix
	return (Tr);
}

t_matrix	set_matrix(t_vector m1, t_vector m2, t_vector m3)
{
	t_matrix	M;

	M.m11 = m1.x; M.m12 = m1.y; M.m13 = m1.z;
	M.m21 = m2.x; M.m22 = m2.y; M.m23 = m2.z;
	M.m31 = m3.x; M.m32 = m3.y; M.m33 = m3.z;
	return (M);
}

t_vector	mul_matrix_vec(t_matrix T, t_vector v)
{
	t_vector	Mv;

	Mv.x = T.m11 * v.x + T.m12 * v.y + T.m13 * v.z;
	Mv.y = T.m21 * v.x + T.m22 * v.y + T.m23 * v.z;
	Mv.z = T.m31 * v.x + T.m32 * v.y + T.m33 * v.z;
	return (Mv);
}

t_matrix	transpose_matrix(t_matrix M)
{
	t_matrix	Mt;

	Mt.m11 = M.m11; Mt.m12 = M.m21; Mt.m13 = M.m31;
	Mt.m21 = M.m12; Mt.m22 = M.m22; Mt.m23 = M.m32;
	Mt.m31 = M.m13; Mt.m32 = M.m23; Mt.m33 = M.m33;
	return (Mt);
}