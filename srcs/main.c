/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 17:33:14 by takira           ###   ########.fr       */
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
	data->win_height = data->win_width * ASPECT_HEIGHT / ASPECT_WIDTH;

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

void	draw_sphere(t_data data, t_vector vec_eye, t_sphere sphere, t_light light)
{
	int			x;
	int			y;
	int			color;
	t_vector	vec_screen;
	float		t;

	y = 0;
	while (y < data.win_height)
	{
		x = 0;
		while (x < data.win_width)
		{
			/* スクリーンのlocal座標(x, y)をworld座標(xw, yw, zw)に変換する */
			vec_screen = tr_screen_dimension_local_to_world(x, y);

			/* 視点位置から(xw, yw)に向かう半直線と球の交差判定を行う */
			if (is_intersect_to_sphere(sphere, vec_eye, vec_screen, &t) == true)
			{
//				printf("(x,y)=(%d,%d), t:%f, ", x, y, t);
				color = shading(vec_eye, vec_screen, light, sphere, t);
			}
			else
				color = CORNFLOWERBLUE;
			my_mlx_pixel_put(&data, x, y, color);

//			t_vector pixel_color = {(float)x / (float)data.win_width, (float)y / (float)data.win_height, (float)0.25};
//			my_mlx_pixel_put(&data, x, y, get_color(pixel_color));
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_data		data;

	t_vector	eye_pos;
	t_vector	screen_dim;

	t_ray		eye_ray;
	t_colorf	color;

	t_scene		scene;

	int			x, y;
	int			r, g, b;

	if (init_data(&data) == FAILURE)
		return (EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	/* init eye & sphere */
	eye_pos = init_vector(0, 0, -5);
	scene_setting(&scene);

	/* draw */
	y = 0;
	while (y < data.win_height)
	{
		x = 0;
		while (x < data.win_width)
		{
			screen_dim = tr_screen_dimension_local_to_world(x, y);
			color = init_color((float)(100/255.0), (float)(149/255.0), (float)(237/255.0));

			eye_ray.start = eye_pos;
			eye_ray.direction = sub(&screen_dim, &eye_pos);

			raytrace(&scene, &eye_ray, &color);

			r = (int)(255 * CLAMP(color.r, 0, 1));
			g = (int)(255 * CLAMP(color.g, 0, 1));
			b = (int)(255 * CLAMP(color.b, 0, 1));

			my_mlx_pixel_put(&data, x, y, r << 16 | g << 8 | b);

			x++;
		}
		y++;
	}

//	draw_sphere(data, eye_pos, sphere, light);

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
