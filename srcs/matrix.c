/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:50:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/02 21:26:57 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_axis(t_vector v)
{
	int		plane;
	float	tmp[3];

	tmp[0] = v.x;
	tmp[1] = v.y;
	tmp[2] = v.z;
	plane = 0;
	if (tmp[plane] > tmp[1])
		plane = 1;
	if (tmp[plane] > tmp[2])
		plane = 2;
	return (plane);
}

t_vector	get_local_axis(t_matrix T, t_vector v)
{
	t_vector	local;

	local.x = T.m11 * v.x + T.m12 * v.y + T.m13 * v.z;
	local.y = T.m21 * v.x + T.m22 * v.y + T.m23 * v.z;
	local.z = T.m31 * v.x + T.m32 * v.y + T.m33 * v.z;
	return (local);
}

t_matrix	rot_matrix(t_vector E)
{
	t_vector	tx, ty, tz;
	float		iX, iY, iZ;
	int			axis;
	t_matrix	R;

	ty = E;
	SET_VECTOR(tx, 0.0f, 0.0f, 0.0f);
	axis = get_axis(E);
	if (axis == 0)
		tx.x = 1;
	else if (axis == 1)
		tx.y = 1;
	else
		tx.z = 1;
	t_vector	tmp;
	tmp = mult(dot(&ty, &tx), &ty);
	tx = sub(&tx, &tmp);
	tx = normalize_vec(&tx);

	tz = cross(&ty, &tx);
	R.m11 = tx.x; R.m12 = tx.y; R.m13 = tx.z;
	R.m21 = ty.x; R.m22 = ty.y; R.m23 = ty.z;
	R.m31 = tz.x; R.m32 = tz.y; R.m33 = tz.z;
	return (R);
}

t_matrix	transpose_matrix(t_matrix R)
{
	t_matrix	T;

	T.m11 = R.m11; T.m12 = R.m21; T.m13 = R.m31;
	T.m21 = R.m12; T.m22 = R.m22; T.m23 = R.m32;
	T.m31 = R.m13; T.m32 = R.m23; T.m33 = R.m33;
	return (T);
}