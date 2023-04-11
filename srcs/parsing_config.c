/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:10:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 14:33:53 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parsing_int_num(const char *line, int *int_num)
{
	size_t	head_idx;
	size_t	len;
	char	*num_str;
	bool	is_success;

	head_idx = 0;
	while (ft_isspace(line[head_idx]))
		head_idx++;
	len = 0;
	while (line[head_idx + len] && !ft_isspace(line[head_idx + len]))
		len++;
	if (!line[head_idx + len])
		return (FAILURE);

	num_str = ft_substr(line, head_idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*int_num = ft_atoi(num_str, &is_success);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}


int	parsing_double_num(const char *line, double *double_num)
{
	size_t	head_idx;
	size_t	len;
	char	*num_str;
	bool	is_success;

	head_idx = 0;
	while (ft_isspace(line[head_idx]))
		head_idx++;
	len = 0;
	while (line[head_idx + len] && !ft_isspace(line[head_idx + len]) && line[head_idx + len] != ',')
		len++;
	if (!line[head_idx + len])
		return (FAILURE);

	num_str = ft_substr(line, head_idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*double_num = ft_strtod(num_str, &is_success);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}

void	skip_delimiter(const char *line, size_t *idx)
{
	while (ft_isspace(line[*idx]))
		*idx += 1;
	if (line[*idx] == ',')
		*idx += 1;
	while (ft_isspace(line[*idx]))
		*idx += 1;
}

int is_vec_in_normal_range(double x, double y, double z)
{
	return ((-1.0 <= x && x <= 1.0) && (-1.0 <= y && y <= 1.0) && (-1.0 <= z && z <= 1.0));
}

int is_rgb_in_range(int r, int g, int b)
{
	return ((0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255));
}


// double_num1, double_num2, double_num3
int parsing_vec(const char *line, t_vector *vec, size_t *idx)
{
	while (ft_isspace(line[*idx]))
		*idx += 1;

	if (parsing_double_num(&line[*idx], &vec->dx) == FAILURE)
		return (FAILURE);

	skip_delimiter(line, idx);

	if (parsing_double_num(&line[*idx], &vec->dy) == FAILURE)
		return (FAILURE);

	skip_delimiter(line, idx);

	if (parsing_double_num(&line[*idx], &vec->dz) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
}

// int_num1, int_num2, int_num3
int parsing_color(const char *line, t_colorf *color, size_t *idx)
{
	while (ft_isspace(line[*idx]))
		*idx += 1;

	if (parsing_int_num(&line[*idx], &color->ir) == FAILURE)
		return (FAILURE);

	skip_delimiter(line, idx);

	if (parsing_int_num(&line[*idx], &color->ig) == FAILURE)
		return (FAILURE);

	skip_delimiter(line, idx);

	if (parsing_int_num(&line[*idx], &color->ib) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
}

// str1, str2
char	*parsing_img_path(const char *line, bool *is_success)
{
	size_t	idx;
	char	*path;

	idx = 0;

	return (path);
}