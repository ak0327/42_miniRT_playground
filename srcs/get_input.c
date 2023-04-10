/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:10:07 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 21:35:23 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_config_line(t_scene *scene, t_camera *camera, char *line)
{

}

int get_scene_config(t_scene *scene, t_camera *camera, const char *path)
{
	int 	fd;
	int		ret_value;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FAILURE);

	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		ret_value = parse_config_line(scene, camera, line);
		free(line);
		if (ret_value == FAILURE)
			break ;
	}
	if (close(fd) < 0)
		return (FAILURE);
	return (ret_value);
}
