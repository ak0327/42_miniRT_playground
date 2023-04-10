/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 14:30:16 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	init_data(t_data *data)
{

	data->win_width = WINDOW_WIDTH;
	data->win_height = WINDOW_HEIGHT;

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

void	free_scene(t_scene scene)
{
	size_t idx;

	idx = 0;
	while (idx < scene.num_shapes)
	{
		free(scene.shapes[idx].material.bump.data);
		free(scene.shapes[idx].material.texture.data);
		idx++;
	}
	free(scene.lights);
	free(scene.shapes);
}

/* **********************

 Coordinates : Left hand

   +y
   |  +z
   | /
   |/_____ +x

 ********************** */

int	main(void)
{
	t_data		data;
	t_ray		eye_ray;
	t_colorf	color;

	t_scene		scene;

	int			i, j;
	int			r, g, b;

	t_camera	camera;
	t_img		bump_img;
	t_img		texture_img;

//	const char	*texture_img_path = "./img/cat.ppm";
//	const char	*img_path = "./img/bump_1.ppm";
//	const char	*img_path = "./img/normal1.ppm";
//	const char	*bump_img_path = "./img/normalmap_example.ppm";
//	const char	*bump_img_path = "./img/1k_earth_normal.ppm";
//	const char	*texture_img_path = "./img/1k_earth.ppm";

	if (init_data(&data) == FAILURE)
		return (EXIT_FAILURE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	/* ppm test */
//	if (get_img(&bump_img, bump_img_path) == FAILURE)
//	{
//		free_data(&data);
//		return (EXIT_FAILURE);
//	}
//	if (get_img(&texture_img, texture_img_path) == FAILURE)
//	{
//		free_data(&data);
//		free_img(&bump_img);
//		return (EXIT_FAILURE);
//	}

//	draw_img_test(data, *img);

//	/* init scene & camera */
	scene_setting(&scene);
	camera = init_camera();

	/* draw */
	j = 0;
	while (j < data.win_height)
	{
		i = 0;
		while (i < data.win_width)
		{
			color = init_color((float)(100.0f/255.0f), (float)(149.0f/255.0f), (float)(237.0f/255.0f));

			eye_ray.start = camera.pos;
			eye_ray.direction = ray_dir(i, j, camera);
			raytrace(&scene, &eye_ray, &color);
			r = (int)(255 * CLAMP(color.r, 0, 1));
			g = (int)(255 * CLAMP(color.g, 0, 1));
			b = (int)(255 * CLAMP(color.b, 0, 1));

			my_mlx_pixel_put(&data, i, j, r << 16 | g << 8 | b);

			i++;
		}
		j++;
	}

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hooks(data);
	mlx_loop(data.mlx);
	free_data(&data);
	free_scene(scene);
	return (0);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}