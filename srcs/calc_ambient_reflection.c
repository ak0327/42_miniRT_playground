/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:11:36 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 11:21:40 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	calc_ambient_reflection(t_colorf ka, t_colorf Ia)
{

	t_colorf				color;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	color = colorf_mul(&color, 1.0f, &ka, 1.0f, &Ia);

	return (color);
}