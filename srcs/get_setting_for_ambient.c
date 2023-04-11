/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_ambient.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:40:05 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 18:40:05 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// A   lightning_ratio[0,1]   RGB[0,255]
int	get_setting_for_ambient(const char *line, t_scene *scene)
{
	size_t		idx;
	float		lightning_ratio;
	t_colorf	color;

	idx = 0;
	if (parsing_double_num(line, &lightning_ratio, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);

	if (lightning_ratio < 0.0f || 1.0f < lightning_ratio)
		return (FAILURE);

	if (!is_color_in_range(color))
		return (FAILURE);

	if (line[idx])
		return (FAILURE);

	scene->ambient_illuminance = get_color_k1c1(lightning_ratio, color);

	return (SUCCESS);
}