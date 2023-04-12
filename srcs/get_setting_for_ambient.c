/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_ambient.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:40:05 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 12:41:21 by takira           ###   ########.fr       */
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
	{
		printf("   ambient NG :: parsing_double_num\n");
		return (FAILURE);
	}
	printf("   ambient :: ratio:%f\n", lightning_ratio);

	if (parsing_color(line, &color, &idx) == FAILURE)
	{
		printf("   ambient NG :: parsing_color\n");
		return (FAILURE);
	}

	if (lightning_ratio < 0.0f || 1.0f < lightning_ratio)
	{
		printf("   ambient NG :: lightning_ratio out of range\n");
		return (FAILURE);
	}

	if (!is_color_in_range(color))
	{
		printf("   ambient NG :: color out of range\n");
		return (FAILURE);
	}

	if (line[idx])
	{
		printf("   ambient NG :: invalid string=[%s]\n", &line[idx]);
		return (FAILURE);
	}

	scene->ambient_illuminance = get_color_k1c1(lightning_ratio, color);

	printf("   ambient OK :)\n");
	return (SUCCESS);
}