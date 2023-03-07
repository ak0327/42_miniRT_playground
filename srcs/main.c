/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/03/07 17:29:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_vector(t_vector *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

int	get_color(t_vector vec)
{
	int r;
	int g;
	int b;
	int	color;

	r = (int)(256 * vec.x);
	g = (int)(256 * vec.y);
	b = (int)(256 * vec.z);
	color = r << 16 | g << 8 | b;
	return (color);
}

int	init_data(t_data *data)
{

	data->win_width = WIN_WIDTH;
	data->win_height = data->win_width * AR_HEIGHT / AR_WIDTH;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (FAILURE);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, WIN_TITLE);
	if (!data->win)
		return (FAILURE);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->img)
		return (FAILURE);
	return (SUCCESS);
}

t_vector	tr_dimension_local_to_world(int x, int y, int w, int h)
{
	t_vector	vec;

	vec.x = (float)2 * (float)x / (float)(w - 1) - 1;
	vec.y = (float) -2 * (float)y / (float)(h - 1) + 1;
	vec.z = 0;
	return (vec);
}

int	main(void)
{
	int		x;
	int		y;
	int		color;
	t_data	data;

	t_vector	vec3;
	t_vector	eye = {0.0f, 0.0f, -5.0f};


	if (init_data(&data) == FAILURE)
		return (EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	y = 0;
	while (y < data.win_height)
	{
		x = 0;
		while (x < data.win_width)
		{
			t_vector pixel_color = {(float)x / (float)data.win_width, (float)y / (float)data.win_height, (float)0.25};
			color = get_color(pixel_color);
			my_mlx_pixel_put(&data, x, y, color);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hooks(data);
	mlx_loop(data.mlx);

	return (0);
}
