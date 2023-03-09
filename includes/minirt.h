/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:42:42 by takira            #+#    #+#             */
/*   Updated: 2023/03/09 10:38:28 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "./../minilibx-linux/mlx.h"
# include "./../libs/include/libft.h"

/********** return value **********/


/********** window **********/
//# define AR_WIDTH	16
//# define AR_HEIGHT	9
//# define WINDOW_WIDTH	384
# define AR_WIDTH		1
# define AR_HEIGHT		1
# define WINDOW_WIDTH	5
# define WINDOW_TITLE	"miniRT"
# define SCREEN_WIDTH	2
# define SCREEN_HEIGHT	2

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

/********** Macro **********/
#define SQR(x) ((x) * (x))
#define MIN(a, b) (a <= b ? a : b)
#define MAX(a, b) (a >= b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

/********** struct **********/
typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;

	int		win_width;
	int		win_height;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct	s_screen
{
	float		cx;
	float		cy;
	float		cz;
	float		screen_width;
	float		screen_height;
	t_vector	normal_vec;
}	t_screen;

typedef struct	s_sphere
{
	float	cx;
	float	cy;
	float	cz;
	float	r;
}	t_sphere;


/********** vector **********/
t_vector	init_vector(float x, float y, float z);
float		dot(const t_vector *a, const t_vector *b);
t_vector	add(const t_vector *a, const t_vector *b);
t_vector	sub(const t_vector *a, const t_vector *b);
t_vector	mult(float k, const t_vector *a);
t_vector	sigma_sum(int num, ...);
float		normalize(t_vector *vec);
void		cross(t_vector *o, t_vector *a, t_vector *b);
const char	*vector_str(const t_vector *vec);
t_vector	copy_vec(const t_vector *a);


/********** screen **********/
t_vector	tr_screen_dimension_local_to_world(int x, int y);


/********** sphere **********/
t_sphere	init_sphere(float x, float y, float z, float r);
//bool		is_intersect_to_sphere(t_sphere sphere, t_vector eye_vec, t_vector vec_screen);


/********** mlx_keyhooks **********/
void	mlx_hooks(t_data data);


#endif //MINIRT_H
