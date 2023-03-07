/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/03/07 12:14:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_square(int s_x, int s_y, int g_x, int g_y, int color, t_data *data)
{
	for (int x=s_x; x<=g_x; x++)
		for (int y=s_y; y<=g_y; y++)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
}

void	init_vector(t_vector *vec, double x, double y, double z)
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

int	main(void)
{
	int		x;
	int		y;
	int		color;
	t_data	data;
	int		win_width;
	int		win_height;

	t_vector	vec3;
	t_vector	pixel_color;

	win_width = WIN_WIDTH;
	win_height = win_width * AR_HEIGHT / AR_WIDTH;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.win = mlx_new_window(data.mlx, win_width, win_height, WIN_TITLE);
	if (!data.win)
		return (EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, win_width, win_height);
	if (!data.img)
		return (EXIT_FAILURE);

	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (x < win_width)
		{
			init_vector(&pixel_color, (double)x / win_width, (double)y / win_height, 0.25);
			color = get_color(pixel_color);
			my_mlx_pixel_put(&data, x, y, color);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_loop(data.mlx);

//
//	y = WIN_HEIGHT;
//	while (y > 0)
//	{
//		x = 0;
//		while (x < WIN_WIDTH)
//		{
//			r = 256 * x / (WIN_WIDTH - 1);
//			g = 256 * y / (WIN_HEIGHT - 1);
//			b = 256 * 0.25;
//			printf("%d, %d, %d\n", r, g, b);
//			x++;
//		}
//		y--;
//	}

	return (0);
}
