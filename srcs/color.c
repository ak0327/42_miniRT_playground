/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:02:44 by takira            #+#    #+#             */
/*   Updated: 2023/03/17 13:54:12 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// c + k1c1 * k2c2
t_colorf	colorf_mul(const t_colorf *c, float k1, const t_colorf *c1, float k2, const t_colorf *c2)
{
	t_colorf	color;

	color.r = c->r + k1 * c1->r * k2 * c2->r;
	color.g = c->g + k1 * c1->g * k2 * c2->g;
	color.b = c->b + k1 * c1->b * k2 * c2->b;
	return (color);
}

// c + k1c1
t_colorf	colorf_muladd(const t_colorf *c, float k1, const t_colorf *c1)
{
	t_colorf	color;

	color.r = c->r + k1 * c1->r;
	color.g = c->g + k1 * c1->g;
	color.b = c->b + k1 * c1->b;
	return (color);
}

t_colorf	colorf_add(const t_colorf *c1, const t_colorf *c2)
{
	t_colorf	color;

	color.r = c1->r + c2->r;
	color.g = c1->g + c2->g;
	color.b = c1->b + c2->b;
	return (color);
}

t_colorf	init_color(float r, float g, float b)
{
	t_colorf	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
