/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:42:42 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 21:37:32 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <float.h>

# include "./../minilibx-linux/mlx.h"
# include "./../libs/include/libft.h"
# include "raycasting.h"
# include "vector.h"

/********** return value **********/


/********** color **********/
# define RED			0xFF0000
# define BLUE			0x0000FF
# define CORNFLOWERBLUE	0x6495ED
# define GRAY			0x808080

/********** window **********/
//# define ASPECT_WIDTH	16
//# define ASPECT_HEIGHT	9
//# define WINDOW_WIDTH	384
# define ASPECT_WIDTH	1
# define ASPECT_HEIGHT	1
# define WINDOW_WIDTH	512
# define WINDOW_TITLE	"miniRT"
# define SCREEN_WIDTH	2
# define SCREEN_HEIGHT	2

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

/********** Macro **********/
#define SQR(x)						((x) * (x))
#define MIN(a, b)					(a <= b ? a : b)
#define MAX(a, b)					(a >= b ? a : b)
#define CLAMP(val, minval, maxval)	MIN(MAX(val, minval), maxval)

#define SET_COLOR(col, r_, g_, b_) { col.r = r_; col.g = g_; col.b = b_; }
#define SET_VECTOR(vec, x_, y_, z_) { vec.x = x_; vec.y = y_; vec.z = z_; }


/********** enum **********/
typedef enum	e_shape_type
{
	ST_SPHERE,
	ST_PLANE,
} t_shape_type;


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
} t_data;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
} t_vector;

typedef struct	s_screen
{
	float		screen_width;
	float		screen_height;
	t_vector	vec_center;
	t_vector	normal_vec;
} t_screen;

typedef struct	s_colorf
{
	float	r;
	float	g;
	float	b;
} t_colorf;

typedef struct	s_ray
{
	t_vector	start;		// 始点
	t_vector	direction;	// 方向ベクトル（単位？）
} t_ray;


typedef struct	s_sphere
{
	float		radius;	// 半径
	t_vector	center;	// 中心
} t_sphere;

typedef struct	s_plane
{
	t_vector	normal;		// 単位法線ベクトル
	t_vector	position;	// planeが通る点の位置ベクトル
} t_plane;


typedef union	u_shape_data // sphere or plane
{
	t_sphere	sphere;
	t_plane		plane;
} t_shape_data;

typedef struct	s_material
{
	t_colorf	ambient_ref;	// ka 環境光反射率RGB
	t_colorf	diffuse_ref;	// kd 拡散反射率RGB
	t_colorf	specular_ref;	// ks 鏡面反射率RGB
	float		shininess;		// alpha 光沢度
} t_material;


typedef struct	s_shape
{
	t_shape_type	type;		// sphere or plane
	t_shape_data	data;		// sphere or plane の情報
	t_material		material;	// 物体表面の質感
} t_shape;


typedef enum	e_light_type
{
	LT_POINT,		// 点光源
	LT_DIRECTIONAL,	// 平行光源
} t_light_type;

typedef struct	s_light
{
	t_light_type	type;		// 点光源 or 平行光源
	t_vector		vector;		// 光源位置 or 光線方向
	t_colorf		illuminance;// 照度RGB
} t_light;

typedef struct	s_scene
{
	t_shape		*shapes;				// 物体リストへのポインタ
	size_t		num_shapes_capacity;	// 物体リストの最大格納数
	size_t		num_shapes;				// 物体リストに格納されている数
	t_light		*lights;				// 光源リストへのポインタ
	size_t		num_lights_capacity;	// 光源リストの最大格納数
	size_t		num_lights;				// 光源リストに格納されている数
	t_colorf	ambient_illuminance;	// 環境光の強さRGB
} t_scene;

typedef struct	s_intersection_point
{
	float		distance;	// 交点までの距離
	t_vector	position;	// 交点の位置ベクトル
	t_vector	normal;		// 交点における物体表面の法線ベクトル
} t_intersection_point;


/********** vector **********/
t_vector	init_vector(float x, float y, float z);
float		dot(const t_vector *a, const t_vector *b);
t_vector	add(const t_vector *a, const t_vector *b);
t_vector	sub(const t_vector *a, const t_vector *b);
t_vector	mult(float k, const t_vector *a);
t_vector	sigma_sum(int num, ...);
float		squared_norm(const t_vector *vec);
float		normalize(t_vector *vec);
void		cross(t_vector *o, t_vector *a, t_vector *b);
const char	*vector_str(const t_vector *vec);
t_vector	copy_vec(const t_vector *a);


/********** screen **********/
t_vector	tr_screen_dimension_local_to_world(int x, int y);


/********** sphere **********/
t_sphere	init_sphere(float x, float y, float z, float r);
bool		is_intersect_to_sphere(t_sphere sphere, t_vector vec_eye, t_vector vec_screen, float *t);


/********** reflection **********/
//t_light		init_light(float x, float y, float z);
int			shading(t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t);


/********** color **********/
t_colorf	init_color(float r, float g, float b);


/********** mlx_keyhooks **********/
void		mlx_hooks(t_data data);


/********** intersection **********/
int intersection_test(const t_shape *shape, const t_ray * ray, t_intersection_point * out_intp);
int get_nearest_shape(const t_scene *scene, const t_ray *ray, float max_dist, int exit_once_found,
					  t_shape **out_shape, t_intersection_point *out_intp);

/********** ray **********/
int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col);


/********** init **********/
void		scene_setting(t_scene *scene);
void		init_shape(t_shape *shape, t_shape_type st, ...);
void init_material(t_material *mat,
				   float ambR, float ambG, float ambB,
				   float difR, float difG, float difB,
				   float speR, float speG, float speB,
				   float shns);

void init_light(t_light *light, t_light_type lt,
				float vx, float vy, float vz,
				float illR, float illG, float illB);


#endif //MINIRT_H
