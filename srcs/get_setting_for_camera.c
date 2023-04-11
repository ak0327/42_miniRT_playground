/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:36:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 18:39:13 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// XYZ : 0.0, 0.0, 0.0
// RGB : 255, 0, 255
// image_path : image_path, bumpmap_path


// C   XYZ   orientation_vec[-1,1]   FOV[0,180]
int get_setting_for_camera(const char *line, t_camera *camera)
{
	size_t		idx;

	idx = 0;
	if (parsing_vec(line, &camera->pos, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &camera->dir, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &camera->fov_deg, &idx) == FAILURE)
		return (FAILURE);

	if (!is_vec_in_normal_range(camera->dir))
		return (FAILURE);

	if (camera->fov_deg < 0.0f || 180.0f < camera->fov_deg)
		return (FAILURE);

	if (line[idx])
		return (FAILURE);

	return (SUCCESS);
}
