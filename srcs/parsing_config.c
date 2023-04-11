/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:10:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 13:47:36 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parsing_num(const char *line, double *num, double lower_limit, double upper_limit)
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
	*num = ft_strtod(num_str, &is_success);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	if (*num < lower_limit && upper_limit < *num)
		return (FAILURE);
	return (SUCCESS);
}

int parsing_point(const char *line, double *x, double *y, double *z)
{
	size_t idx;

	idx = 0;

	return (SUCCESS);
}

int parsing_color(const char *line, int *r, int *g, int *b)
{
	size_t idx;

	idx = 0;

	return (SUCCESS);
}

int parsing_norm_vec(const char *line, double *x, double *y, double *z)
{
	size_t idx;

	idx = 0;

	return (SUCCESS);
}

char	*parsing_img_path(const char *line, bool *is_success)
{
	size_t	idx;
	char	*path;

	idx = 0;

	return (path);
}