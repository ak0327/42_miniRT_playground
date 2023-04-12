/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:10:07 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 12:42:12 by takira           ###   ########.fr       */
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
	size_t	len;

	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
	len = 0;
	while (line[*idx + len] && !ft_isspace(line[*idx + len]))
		len++;
	id_str = ft_substr(line, *idx, len);
	if (!id_str)
		return (NULL);
	*idx += len;
	return (id_str);
}

static int get_params_for_identifier(int id_no, const char *line, t_scene *scene, t_camera *camera)
{
	int ret_value;

	ret_value = FAILURE;
	if (id_no == id_camera)
	{
		ret_value = get_setting_for_camera(line, camera);
		printf("  get_params -> camera_ret=%d\n", ret_value);
	}
	else if (id_no == id_ambient)
	{
		ret_value = get_setting_for_ambient(line, scene);
		printf("  get_params -> ambient_ret=%d\n", ret_value);
	}
	else if (id_no == id_point_light || id_no == id_spot_light)
	{
		ret_value = get_setting_for_lights(line, scene, id_no);
		printf("  get_params -> light_ret=%d\n", ret_value);
	}
	else if (id_no == id_plane || id_no == id_sphere || id_no == id_cylinder || id_no == id_corn)
	{
		ret_value = get_setting_for_objects(line, scene, id_no);
		printf("  get_params -> objects_ret=%d\n", ret_value);
	}
	printf("  get_params :: ret=%d\n", ret_value);
	return (ret_value);
}

static int increment_idx_to_next_char(const char *line, size_t *idx)
{
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
	while (line[idx] && ft_isspace(line[idx]))
		idx++;

	if (!line[idx])
		return (SUCCESS);
	printf("\n\n");
	// get_identifier
	id_str = get_identifier(line, &idx);
	if (!id_str)
	{
		printf(" Error: id_str == NULL (parse_config_line)\n");
		return (FAILURE);
	}
	printf("id:%s\n", id_str);

	// valid id_str
	id_no = get_identifier_no(id_str);
	free(id_str);
	if (id_no == INVALID_ID)
	{
		printf(" Error: invalid id (parse_config_line)\n");
		return (FAILURE);
	}

	if (increment_idx_to_next_char(line, &idx) == FAILURE)
	{
		printf(" Error: increment idx (parse_config_line)\n");
		return (FAILURE);
	}

	// get_params_for_identifier
	if (get_params_for_identifier(id_no, &line[idx], scene, camera) == FAILURE)
	{
		printf(" Error: get_params_for_identifier (parse_config_line)\n");
		return (FAILURE);
	}
	printf(" OK: parse_config_line\n");

	return (SUCCESS);
}

static int	parsing_config_line_by_line(t_scene *scene, t_camera *camera, int fd)
{
	char	*line;
	int		ret_value;

	ret_value = SUCCESS;
	printf("## gnl START ##\n");
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		ret_value *= parse_config_line(scene, camera, line);
		free(line);
	}
	printf("## gnl END ##\n");
	return (ret_value);
}

int get_scene_config(t_scene *scene, t_camera *camera, const char *path)
{
	int 	fd;
	int		ret_value;

	scene->light_list = NULL;
	scene->shape_list = NULL;

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
