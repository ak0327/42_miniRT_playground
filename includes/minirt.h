/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:42:42 by takira            #+#    #+#             */
/*   Updated: 2023/03/08 12:14:52 by takira           ###   ########.fr       */
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
//# define WIN_WIDTH	384
# define AR_WIDTH	1
# define AR_HEIGHT	1
# define WIN_WIDTH	5
# define WIN_TITLE	"miniRT"

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

/********** vector **********/
void		init_vector(t_vector *vec, float x, float y, float z);
float		dot(const t_vector *a, const t_vector *b);
t_vector	add(const t_vector *a, const t_vector *b);
t_vector	sub(const t_vector *a, const t_vector *b);
t_vector	mult(float k, const t_vector *a);
t_vector	sigma_sum(int num, ...);
float		normalize(t_vector *vec);
void		cross(t_vector *o, t_vector *a, t_vector *b);
const char	*vector_str(const t_vector *vec);


/********** screen **********/
t_vector	tr_screen_dimension_local_to_world(int x, int y, int w, int h);

/********** sphere **********/


/********** mlx_keyhooks **********/
void	mlx_hooks(t_data data);


#endif //MINIRT_H
