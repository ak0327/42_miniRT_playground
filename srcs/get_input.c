/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:10:07 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 21:41:21 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_config_line(t_scene *scene, t_camera *camera, char *line)
{

}

int	parsing_config_line_by_line(t_scene *scene, t_camera *camera, int fd)
{
	char	*line;
	int		ret_value;

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
	return (ret_value);
}

int get_scene_config(t_scene *scene, t_camera *camera, const char *path)
{
	int 	fd;
	int		ret_value;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (PROCESS_ERROR);
	}

	ret_value = parsing_config_line_by_line(scene, camera, fd);

	if (close(fd) < 0)
	{
		perror("close");
		return (PROCESS_ERROR);
	}
	return (ret_value);
}
