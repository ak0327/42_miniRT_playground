/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/03/08 10:14:13 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void	free_data(t_data *data)
{
	if (!data)
		return ;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}


int	main(void)
{
	int		x;
	int		y;
	t_data	data;

	if (init_data(&data) == FAILURE)
		return (EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	// 視点を決める
	t_vector	eye = {0.0f, 0.0f, -5.0f};

	y = 0;
	while (y < data.win_height)
	{
		x = 0;
		while (x < data.win_width)
		{
			// 視点位置から(x, y)に向かう半直線と球の交差判定


			// 球と交差する場合	-> Red
			// そうでない場合 	-> Blue


//			t_vector pixel_color = {(float)x / (float)data.win_width, (float)y / (float)data.win_height, (float)0.25};
//			my_mlx_pixel_put(&data, x, y, get_color(pixel_color));
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hooks(data);
	mlx_loop(data.mlx);
	free_data(&data);
	return (0);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}