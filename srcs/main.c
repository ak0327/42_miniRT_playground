/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/03/06 17:38:30 by takira           ###   ########.fr       */
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

int	main(void)
{
	int		x;
	int		y;
	int		r, g, b;
	int		color;
	t_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, TITLE);
	if (!data.win)
		return (EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img)
		return (EXIT_FAILURE);

	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = 256 * x / (WIDTH);
			g = 256 * y / (HEIGHT);
			b = 256 * 0.25;
			color = r << 16 | g << 8 | b;
			my_mlx_pixel_put(&data, x, y, color);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_loop(data.mlx);

//
//	y = HEIGHT;
//	while (y > 0)
//	{
//		x = 0;
//		while (x < WIDTH)
//		{
//			r = 256 * x / (WIDTH - 1);
//			g = 256 * y / (HEIGHT - 1);
//			b = 256 * 0.25;
//			printf("%d, %d, %d\n", r, g, b);
//			x++;
//		}
//		y--;
//	}

	return (0);
}
