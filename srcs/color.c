/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:02:44 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 17:22:26 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	init_color(float r, float g, float b)
{
	t_colorf	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
