/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ppm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:28:37 by takira            #+#    #+#             */
/*   Updated: 2023/04/05 17:00:19 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*free_split_array_ret_nullptr(char **split)
{
	size_t idx;

	if (!split)
		return (NULL);
	idx = 0;
	while (split[idx])
	{
		free(split[idx]);
		idx++;
	}
	free(split);
	return (NULL);
}

void	*free_line_ret_nullptr(char *line)
{
	size_t idx;

	if (!line)
		return (NULL);
	free(line);
	return (NULL);
}

t_img	*get_ppm(void)
{
	t_img		*img;
	const char	*img_path = "./img/cat.ppm";
	char		*line;
	char		**split;
	size_t		col;
	size_t		row;
	size_t		idx;
	int			fd;
	bool		is_atoi_success;

	fd = open(img_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (NULL);

	col = 0;
	idx = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		if (!split)
			return (NULL); // free
		if (col == 2)
		{
			//todo: check array len, atoi success or failure
			img->width = ft_atoi(split[0], &is_atoi_success);
			img->height = ft_atoi(split[1], &is_atoi_success);
			printf("w:%d, h:%d\n", img->width, img->height);
			img->data = (int *)ft_calloc(sizeof(int), img->width * 3 * img->height);
		}
		else if (col >= 4)
		{
			row = 0;
			while (split[row])
			{
				img->data[idx] = ft_atoi(split[row], &is_atoi_success);
				row++;
				idx++;
			}
		}
		line = free_line_ret_nullptr(line);
		split = free_split_array_ret_nullptr(split);
		col++;
	}
	return (img);
}

void	draw_img_test(t_data data, t_img img)
{
	int			x, y;
	int			r, g, b;
	size_t		idx;

	idx = 0;
	y = 0;
	while (y < data.win_height)
	{
		x = 0;
		while (x < data.win_width)
		{
			r = 0; g = 0, b = 0;
			if ((idx / 3) / img.width < y && (idx / 3)  < img.width * img.height)
			{
				r = img.data[idx++];
				g = img.data[idx++];
				b = img.data[idx++];
			}
			my_mlx_pixel_put(&data, x, y, r << 16 | g << 8 | b);
			x++;
		}
		y++;
	}

}