/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/03/09 11:39:23 by takira           ###   ########.fr       */
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

	data->win_width = WINDOW_WIDTH;
	data->win_height = data->win_width * AR_HEIGHT / AR_WIDTH;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (FAILURE);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, WINDOW_TITLE);
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
	t_data		data;

	t_vector	vec_eye;
	t_vector	vec_screen;
//	t_vector	vec_eye2screen;
	t_sphere	sphere;

	int			color;

	int			red = 0xFF0000;
	int			blue = 0x0000FF;

	int			x;
	int			y;

	if (init_data(&data) == FAILURE)
		return (EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	/* 視点を決める */
	vec_eye = init_vector(0, 0, -5);
	sphere = init_sphere(0, 0, 5, 1);

	y = 0;
	while (y < data.win_height)
	{
		x = 0;
		while (x < data.win_width)
		{
			/* スクリーンのlocal座標(x, y)をworld座標(xw, yw, zw)に変換する */
			vec_screen = tr_screen_dimension_local_to_world(x, y);
//			printf("local2world: (x,y)=(%d,%d), vec:%s\qn", x, y, vector_str(&vec_screen));

			/* 視点位置から(xw, yw)に向かう半直線と球の交差判定を行う */
			if (is_intersect_to_sphere(sphere, vec_eye, vec_screen) == true)
				color = red;
			else
				color = blue;
			my_mlx_pixel_put(&data, x, y, color);

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
