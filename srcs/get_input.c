/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:10:07 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 12:43:47 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		get_identifier_no(const char *id_str)
{
	const char		*ids[] = { "C", "A","L", "sl", "sp", "pl", "cy", "co", NULL};
	size_t			idx;

	idx = 0;
	while (ids[idx])
	{
		if (is_same_str(id_str, ids[idx]))
			return ((int)idx);
		idx++;
	}
	return (INVALID_ID);
}

char	*get_identifier(const char *line, size_t *idx)
{
	char	*id_str;

	while (line[*idx] && !ft_isspace(line[*idx]))
		*idx += 1;
	if (!line[*idx])
		return (NULL);
	id_str = ft_substr(line, 0, *idx);
	if (!id_str)
		return (NULL);
	return (id_str);
}

int get_params_for_identifier(int id_no, const char *line, t_scene *scene, t_camera *camera)
{
	int ret_value;

	if (id_no == id_camera)
		ret_value = get_setting_for_camera(line, camera);
	else if (id_no == id_ambient)
		ret_value = get_setting_for_ambient(line, scene);
	else if (id_no == id_point_light || id_no == id_spot_light)
		ret_value = get_setting_for_lights(line, scene);
	else
		ret_value = get_setting_for_objects(line, scene);
	return (ret_value);
}

int increment_idx_to_next_char(const char *line, const char *id_str, size_t *idx)
{
	*idx += ft_strlen_ns(id_str);
	while (ft_isspace(line[*idx]))
		*idx += 1;
	if (!line[*idx])
		return (FAILURE);
	return (SUCCESS);
}

static int parse_config_line(t_scene *scene, t_camera *camera, const char *line)
{
	size_t	idx;
	char	*id_str;
	int		id_no;

	idx = 0;
	while (ft_isspace(line[idx]))
		idx++;

	// get_identifier
	id_str = get_identifier(line, &idx);
	if (!id_str)
		return (FAILURE);

	// valid id_str
	id_no = get_identifier_no(id_str);
	if (id_no == INVALID_ID)
		return (FAILURE);

	if (increment_idx_to_next_char(line, id_str, &idx) == FAILURE)
		return (FAILURE);

	// get_params_for_identifier
	if (get_params_for_identifier(id_no, &line[idx], scene, camera) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
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

	// todo:dir or file
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
