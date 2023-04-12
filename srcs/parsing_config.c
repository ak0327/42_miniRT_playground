/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:10:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 12:38:46 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// todo:float -> int, 今回は変更面倒なのでfloatで進める
int	parsing_int_num(const char *line, float *int_num, size_t *idx)
{
	size_t	len;
	char	*num_str;
	bool	is_success;

	while (ft_isspace(line[*idx]))
		*idx += 1;
	len = 0;
	while (line[*idx + len] && !ft_isspace(line[*idx + len]))
		len++;
	if (!line[*idx + len])
		return (FAILURE);

	num_str = ft_substr(line, *idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*idx += len;
	*int_num = (float)ft_atoi(num_str, &is_success);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}


int	parsing_double_num(const char *line, float *double_num, size_t *idx)
{
	size_t	len;
	char	*num_str;
	bool	is_success;

	while (ft_isspace(line[*idx]))
		*idx += 1;
	len = 0;
	while (line[*idx + len] && !ft_isspace(line[*idx + len]) && line[*idx + len] != ',')
		len++;

	num_str = ft_substr(line, *idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*idx += len;
	*double_num = (float)ft_strtod(num_str, &is_success);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}

void	skip_delimiter(const char *line, size_t *idx)
{
	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
	if (line[*idx] == ',')
		*idx += 1;
	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
}

int is_vec_in_normal_range(t_vector vec)
{
	const float x = vec.x;
	const float y = vec.y;
	const float z = vec.z;

	return ((-1.0f <= x && x <= 1.0f) && (-1.0f <= y && y <= 1.0f) && (-1.0f <= z && z <= 1.0f));
}

int is_color_in_range(t_colorf color)
{
	const float	r = color.r;
	const float	g = color.g;
	const float	b = color.b;

	return ((0.0f <= r && r <= 255.0f) && (0.0f <= g && g <= 255.0f) && (0.0f <= b && b <= 255.0f));
}

// double_num1, double_num2, double_num3
int parsing_vec(const char *line, t_vector *vec, size_t *idx)
{
	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;

	if (parsing_double_num(line, &vec->x, idx) == FAILURE)
	{
		printf("    parsing_vec NG :: parsing_double_num 1\n");
		return (FAILURE);
	}

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &vec->y, idx) == FAILURE)
	{
		printf("    parsing_vec NG :: parsing_double_num 2\n");
		return (FAILURE);
	}

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &vec->z, idx) == FAILURE)
	{
		printf("    parsing_vec NG :: parsing_double_num 3\n");
		return (FAILURE);
	}

	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;

	printf("    parsing_vec :: SUCCESS, (x,y,z)=(%f,%f,%f)\n", vec->x, vec->y, vec->z);

	return (SUCCESS);
}

// int_num1, int_num2, int_num3
int parsing_color(const char *line, t_colorf *color, size_t *idx)
{
	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;

	if (parsing_double_num(line, &color->r, idx) == FAILURE)
	{
		printf("    parsing_color NG :: parsing_int_num 1, r:%d\n", (int)color->r);
		return (FAILURE);
	}
//	printf("    parsing_color :: r:%f\n", color->r);

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &color->g, idx) == FAILURE)
	{
		printf("    parsing_color NG :: parsing_int_num 2\n");
		return (FAILURE);
	}
//	printf("    parsing_color :: g:%f\n", color->g);

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &color->b, idx) == FAILURE)
	{
		printf("    parsing_color NG :: parsing_int_num 3\n");
		return (FAILURE);
	}
//	printf("    parsing_color :: b:%f\n", color->b);

	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;

	printf("    parsing_color :: SUCCESS, (r,g,b)=(%f,%f,%f)\n", color->r, color->g, color->b);
	return (SUCCESS);
}

// str1, str2
char	*parsing_img_path(const char *line, size_t *idx)
{
	char	*path;

	path = get_identifier(line, idx);
	return (path);
}