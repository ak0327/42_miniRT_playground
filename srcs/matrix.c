/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:50:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/06 21:38:47 by takira           ###   ########.fr       */
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

t_matrix	set_matrix(t_vector m1, t_vector m2, t_vector m3)
{
	t_matrix	M;

	M.m11 = m1.x; M.m12 = m1.y; M.m13 = m1.z;
	M.m21 = m2.x; M.m22 = m2.y; M.m23 = m2.z;
	M.m31 = m3.x; M.m32 = m3.y; M.m33 = m3.z;
	return (M);
}

t_vector	matrix_x_vec(t_matrix T, t_vector v)
{
	t_vector	Mv;

	Mv.x = T.m11 * v.x + T.m12 * v.y + T.m13 * v.z;
	Mv.y = T.m21 * v.x + T.m22 * v.y + T.m23 * v.z;
	Mv.z = T.m31 * v.x + T.m32 * v.y + T.m33 * v.z;
	return (Mv);
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

t_matrix	transpose_matrix(t_matrix M)
{
	t_matrix	Mt;

	Mt.m11 = M.m11; Mt.m12 = M.m21; Mt.m13 = M.m31;
	Mt.m21 = M.m12; Mt.m22 = M.m22; Mt.m23 = M.m32;
	Mt.m31 = M.m13; Mt.m32 = M.m23; Mt.m33 = M.m33;
	return (Mt);
}