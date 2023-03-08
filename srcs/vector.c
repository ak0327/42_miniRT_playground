/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:48:43 by takira            #+#    #+#             */
/*   Updated: 2023/03/08 19:00:32 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdarg.h>

t_vector	init_vector(float x, float y, float z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector copy_vec(const t_vector *a)
{
	t_vector	vec;

	vec.x = a->x;
	vec.y = a->y;
	vec.z = a->z;
	return (vec);
}

t_vector mult(float k, const t_vector *a)
{
	t_vector	vec;

	vec.x = k * a->x;
	vec.y = k * a->y;
	vec.z = k * a->z;
	return (vec);
}

t_vector	add(const t_vector *a, const t_vector *b)
{
	t_vector	vec;

	vec.x = a->x + b->x;
	vec.y = a->y + b->y;
	vec.z = a->z + b->z;
	return (vec);
}

t_vector sub(const t_vector *a, const t_vector *b)
{
	t_vector	vec;

	vec.x = a->x - b->x;
	vec.y = a->y - b->y;
	vec.z = a->z - b->z;
//	printf("sub: a:%s\n", vector_str(a));
//	printf("     b:%s\n", vector_str(b));
//	printf("     vec:%s\n\n", vector_str(&vec));
	return (vec);
}

/* num: num of args    */
/* k1, v1, k2, v2, ... */
t_vector	sigma_sum(int num, ...)
{
	va_list		ap;
	t_vector	vec;
	float		ki;
	t_vector	vi;
	int			i;

	init_vector(&vec, 0, 0, 0);
	i = 0;
	va_start(ap, num);
	va_arg(ap, int);
	while (i < num)
	{
		ki = va_arg(ap, double);
		vi = va_arg(ap, t_vector);
//		printf("ki:%lf, vi:%s\n", ki, vector_str(&vi));
		vec.x += ki * (&vi)->x;
		vec.y += ki * (&vi)->y;
		vec.z += ki * (&vi)->z;
		i++;
	}
	va_end(ap);
	return (vec);
}

float	dot(const t_vector *a, const t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
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
