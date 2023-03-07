/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:42:42 by takira            #+#    #+#             */
/*   Updated: 2023/03/06 20:38:06 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>

# include "../minilibx-linux/mlx.h"

# define AR_WIDTH	16
# define AR_HEIGHT	9
# define WIN_WIDTH	384
# define WIN_TITLE	"miniRT"

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;


typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

#endif //MINIRT_H
