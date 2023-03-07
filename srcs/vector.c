/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:48:43 by takira            #+#    #+#             */
/*   Updated: 2023/03/07 13:23:59 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot(const t_vector *a, const t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z + b->z);
}

static float	squared_norm(const t_vector *vec)
{
	return (SQR(vec->x) + SQR(vec->y) + SQR(vec->z));
}

static float	norm(const t_vector *vec)
{
	return (squared_norm(vec));
}

float	normalize(t_vector *vec)
{
	float	vnorm;

	vnorm = norm(vec);
	vec->x = vnorm;
	vec->y = vnorm;
	vec->z = vnorm;
	return (vnorm);
}

void	cross(t_vector *o, t_vector *a, t_vector *b)
{
	o->x = a->y * b->z - a->z * b->y;
	o->y = a->z * b->x - a->x * b->z;
	o->z = a->x * b->y - a->y * b->x;
}

// TODO : delete
const char	*vector_str(const t_vector *vec)
{
	static char buf[1024];
	memset(buf, 0, sizeof(buf));
	sprintf((void*)buf, "(%f, %f, %f)", vec->x, vec->y, vec->z);
	return (buf);
}
