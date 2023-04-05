/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ppm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:28:37 by takira            #+#    #+#             */
/*   Updated: 2023/04/05 21:44:47 by takira           ###   ########.fr       */
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
//	const char	*img_path = "./img/cat.ppm";
//	const char	*img_path = "./img/bump_1.ppm";
	const char	*img_path = "./img/normal1.ppm";
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
//			printf("w:%d, h:%d\n", img->width, img->height);
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

t_colorf	get_img_color(const t_scene *scene, const t_ray *eye_ray,
							  t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	pos_local;
	t_vector	bamp_n;
	int			r, g, b;
	size_t		row, col, idx;
	int			put_size = 2;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	if (shape->type == ST_PLANE)
	{

		int	u, v;
		u = (int)intp.position.x;
		v = (int)intp.position.z;
		v = -v;

		row = (((u * put_size)  % img.width) + img.width) % img.width;
		col = (((v * put_size) % img.height) + img.height) % img.height;

		idx = ((col * img.width + row) * 3) % (img.width * img.height * 3);
		r = img.data[idx++];
		g = img.data[idx++];
		b = img.data[idx];
		bamp_n.x = (float)r; bamp_n.y = (float)g, bamp_n.z = (float)b;
		normalize(&bamp_n);

		intp.normal = bamp_n;

		SET_COLOR(color, (float)r/255.0f, (float)g/255.0f, (float)b/255.0f);
		return (color);
	}
//	else if (shape->type == ST_SPHERE)
//	{
//		pos_local = sub(&intp.position, &shape->data.sphere.center);
//		float radius = norm(&pos_local);
//		float theta = acosf(pos_local.y / radius);
//		float phi = atan2f(pos_local.z, pos_local.x);
//		float u = 1.0f - phi / (float)M_PI;
//		float v = 1.0f - (theta / (2.0f * (float)M_PI) + 0.5f);
//		condition_checker = (int)(floorf(u * 10) + floorf(v * 15)) % 2;
//		if (condition_checker)
//		{
//			SET_COLOR(color, 0.6f, 0.6f, 0.6f);
//			color = colorf_add(&color, &color);
//		}
//	}
//	else if (shape->type == ST_CYLINDER || shape->type == ST_CORN)
//	{
//		/* u,v */
//		t_vector	hi, d;
//		if (shape->type == ST_CYLINDER)
//		{
//			pos_local = sub(&intp.position, &shape->data.cylinder.position);
//			hi = mult(dot(&pos_local, &shape->data.cylinder.normal), &shape->data.cylinder.normal);
//			d = shape->data.cylinder.normal;
//		}
//		else
//		{
//			pos_local = sub(&intp.position, &shape->data.corn.position);
//			hi = mult(dot(&pos_local, &shape->data.corn.normal), &shape->data.corn.normal);
//			d = shape->data.corn.normal;
//		}
//
//		t_vector	u_vec, v_vec;
//		float		theta;
//		float	u, v, uu, vv;
//
//		u_vec.x = d.y / sqrtf(SQR(d.x) + SQR(d.y));		// TODO: +-
//		u_vec.y = -d.x / sqrtf(SQR(d.x) + SQR(d.y));	// TODO: +-
//		u_vec.z = 0;
//		normalize(&u_vec);
//
//		v_vec = cross(&u_vec, &d);
//		normalize(&v_vec);
//
//		u = dot(&u_vec, &pos_local);
//		v = dot(&v_vec, &pos_local);
//
//		theta = atan2f(v, u);
//		uu = 1.0f - (theta / (2.0f * (float)M_PI) + 0.5f);
//		vv = norm(&hi);
//
//		condition_checker = (int)(floorf(uu * 10) + floorf(vv * 1)) % 2;
//
//		if (condition_checker)
//		{
//			SET_COLOR(color, 1.0f, 1.0f, 1.0f);
//			color = colorf_add(&color, &color);
//		}
//
//	}
	return (color);
}
