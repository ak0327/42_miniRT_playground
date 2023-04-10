/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:42:42 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 14:35:37 by takira           ###   ########.fr       */
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
# define COLOR_A	0
# define COLOR_B	1

/********** color **********/
# define RED			0xFF0000
# define BLUE			0x0000FF
# define CORNFLOWERBLUE	0x6495ED
# define GRAY			0x808080

/********** window **********/
//# define ASPECT_WIDTH	16
//# define ASPECT_HEIGHT	9
//# define WINDOW_WIDTH	384
//# define ASPECT_WIDTH	1
//# define ASPECT_HEIGHT	1
# define ASPECT				(16.0f / 9.0f)
# define WINDOW_HEIGHT		540
# define WINDOW_WIDTH		960
# define WINDOW_TITLE		"miniRT"
//# define SCREEN_WIDTH	2
//# define SCREEN_HEIGHT	2

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

/********** Macro **********/
#define SQR(x)		((x) * (x))
#define MIN(a, b)	(a <= b ? a : b)
#define MAX(a, b)	(a >= b ? a : b)
#define ABS(x)		(x >= 0 ? x : -1 * x)

#define CLAMP(val, minval, maxval)	MIN(MAX(val, minval), maxval)

#define SET_COLOR(col, r_, g_, b_)	{ col.r = r_; col.g = g_; col.b = b_; }
#define SET_VECTOR(vec, x_, y_, z_)	{ vec.x = x_; vec.y = y_; vec.z = z_; }


//#define EPSILON			(1.0f / 512.0f)
//#define EPSILON			(1.0f / 256.0f)
//#define EPSILON			(1.0f / 128.0f)
//#define EPSILON			(1.0f / 64.0f)
#define EPSILON			(1.0f / 32.0f)

#define MAX_RECURSION	8


/********** enum **********/
typedef enum	e_shape_type
{
	ST_PLANE,
	ST_SPHERE,
	ST_CYLINDER,
	ST_CORN,
	ST_HYPERBOLOID,
	ST_PARABOLOID,
	ST_TRIANGLE,
} t_shape_type;

typedef enum	e_light_type
{
	LT_POINT,		// 点光源
	LT_DIRECTIONAL,	// 平行光源
	LT_SPOT,
} t_light_type;

typedef enum	e_material_type
{
	MT_DEFAULT,		// 通常の質感
	MT_PERFECT_REFLECTION,	// 完全鏡面反射
	MT_REFRACTION,	// 完全鏡面反射・屈折
} t_material_type;

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

typedef struct s_matrix
{
	float	m11, m12, m13;
	float	m21, m22, m23;
	float	m31, m32, m33;
} t_matrix;

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

typedef struct	s_img
{
	int	height;
	int width;
	int	*data;	// data=[R11,G11,B11, R12,G12,B12, ..., R21,G21,B21,..., Rhw,Ghw,Bhw]
} t_img;

typedef struct	s_ray
{
	t_vector	start;		// 始点
	t_vector	direction;	// 方向ベクトル（単位？）
} t_ray;


typedef struct	s_plane
{
	t_vector	normal;		// 単位法線ベクトル
	t_vector	position;	// planeが通る点の位置ベクトル
	float		checker_width;
} t_plane;

typedef struct	s_sphere
{
	float		radius;	// 半径
	t_vector	center;	// 中心
} t_sphere;

typedef struct	s_cylinder
{
	t_vector	normal;		// 単位法線ベクトル todo:direction
	t_vector	position;	// 中心位置ベクトル
	float		height;
	float		radius;
} t_cylinder;

typedef struct	s_corn
{
	t_vector	normal;		// 単位法線ベクトル todo:direction
	t_vector	position;	// 底面中心位置ベクトル
	t_vector	origin;		// 中心位置（先端）ベクトル
	float		height;
	float		radius;
} t_corn;


typedef struct	s_hyperboloid
{
	t_vector	normal;		// 単位法線ベクトル todo:direction
	t_vector	position;	// 中心位置ベクトル
	float		height;
	float		radius;
} t_hyperboloid;

typedef struct	s_paraboloid
{
	t_vector	normal;		// 単位法線ベクトル todo:direction
	t_vector	position;	// 中心位置ベクトル
	float		height;
	float		radius;
} t_paraboloid;


typedef union	u_shape_data // sphere or plane
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_corn			corn;
	t_hyperboloid	hyperboloid;
	t_paraboloid	paraboloid;

} t_shape_data;

typedef struct	s_material
{
	t_colorf		ambient_ref;	// ka 環境光反射率RGB
	t_colorf		diffuse_ref;	// kd 拡散反射率RGB
	t_colorf		diffuse_ref_checker;	// kd 拡散反射率RGB

	t_colorf		specular_ref;	// ks 鏡面反射率RGB
	float			shininess;		// alpha 光沢度

	t_material_type	type;			// default or 完全鏡面反射
	t_colorf		reflect_ref;	// kf 完全鏡面反射光/屈折光係数RGB
	float			refraction_index;	// 絶対屈折率

	t_img			texture;
	t_img			bump;
	bool			is_checker;

} t_material;

typedef struct	s_shape
{
	t_shape_type	type;		// sphere or plane
	t_shape_data	data;		// sphere or plane の情報
	t_material		material;	// 物体表面の質感
} t_shape;

typedef struct	s_light
{
	t_light_type	type;			// point, directional or spot
	t_vector		position;		// 光源位置 or 光線方向（*光線への方向？光線からの方向？）
	t_vector		direction;
	t_colorf		illuminance;	// 光源の照度 Ii RGB
	float			angle;			// spot_light, angle
} t_light;

typedef struct	s_scene
{
	t_shape		*shapes;				// 物体リストへのポインタ
	size_t		num_shapes_capacity;	// 物体リストの最大格納数
	size_t		num_shapes;				// 物体リストに格納されている数
	t_light		*lights;				// 光源リストへのポインタ
	size_t		num_lights_capacity;	// 光源リストの最大格納数
	size_t		num_lights;				// 光源リストに格納されている数
	t_colorf	ambient_illuminance;	// 環境光の強さIa RGB
	float		global_refraction_index;// 大気の絶対屈折率
} t_scene;

typedef struct	s_intersection_point
{
	float		distance;	// 交点までの距離
	t_vector	position;	// 交点の位置ベクトル
	t_vector	normal;		// 交点における物体表面の法線ベクトル
} t_intersection_point;

typedef struct	s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_vector	vec_camera_to_sc_center;
	t_matrix	transpose_matrix_w2c;
	t_matrix	transpose_matrix_c2w;
	float		distance_camera_to_sc;
	float		fov_deg;
} t_camera;

typedef struct	s_texture_map
{
	float	u;
	float	v;
} t_texture_map;


/********** vector **********/
t_vector	init_vector(float x, float y, float z);
float		dot(const t_vector *a, const t_vector *b);
t_vector	add(const t_vector *a, const t_vector *b);
t_vector	sub(const t_vector *a, const t_vector *b);
t_vector	mult(float k, const t_vector *a);
t_vector	sigma_sum(int num, ...);
float		squared_norm(const t_vector *vec);
float		norm(const t_vector *vec);
float		normalize(t_vector *vec);
t_vector	cross(const t_vector *a, const t_vector *b);
//void		cross(t_vector *o, t_vector *a, t_vector *b);
const char	*vector_str(const t_vector *vec);
t_vector	copy_vec(const t_vector *a);
t_vector	vec_calc(float k1, t_vector *a, float k2, t_vector *b);
t_vector	normalize_vec(const t_vector *a);
t_vector	normalize_vec_inv(const t_vector *a);


/********** screen **********/
t_vector	ray_dir(int x, int y, t_camera camera);


/********** camera **********/
t_camera	init_camera(void);


/********** sphere **********/
t_sphere	init_sphere(float x, float y, float z, float r);
bool		is_intersect_to_sphere(t_sphere sphere, t_vector vec_eye, t_vector vec_screen, float *t);


/********** reflection **********/
//t_light		init_light(float x, float y, float z);
int			shading(t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t);


/********** color **********/
t_colorf	init_color(float r, float g, float b);
//t_colorf	colorf_mul(t_colorf c, float k1, t_colorf c1, float k2, t_colorf c2);
//t_colorf	colorf_mul(t_colorf *c, float k1, t_colorf *c1, float k2, t_colorf *c2);
t_colorf	colorf_mul(const t_colorf *c, float k1, const t_colorf *c1, float k2, const t_colorf *c2);
t_colorf	colorf_add(const t_colorf c1, const t_colorf c2);
t_colorf	colorf_muladd(const t_colorf c, float k1, const t_colorf c1);

/********** mlx_keyhooks **********/
void		mlx_hooks(t_data data);


/********** intersection **********/
int			intersection_test(t_shape *shape, const t_ray * ray, t_intersection_point * out_intp);
int			get_nearest_shape(const t_scene *scene, const t_ray *ray, float max_dist, int exit_once_found,
					  t_shape **out_shape, t_intersection_point *out_intp);

/********** checker **********/
t_colorf	get_checker_color(t_intersection_point intp, t_shape *shape);


/********** texture_map **********/
t_texture_map	get_cylindrical_map(t_vector pos_local, t_matrix Tr, float h);
t_texture_map	get_conical_map(t_vector pos_local, t_matrix Tr, float h);
t_texture_map	get_spherical_map(t_vector pos_local);
t_texture_map	get_planar_map(t_vector pos_local, t_matrix Tr);


/********** matrix **********/
t_matrix	rot_matrix(t_vector E);
t_matrix	transpose_matrix(t_matrix R);
t_matrix	set_vec_to_matrix(t_vector m1, t_vector m2, t_vector m3);
t_vector	mul_matrix_vec(t_matrix T, t_vector v);
t_matrix	get_tr_matrix_world2obj_zup(t_vector w_dir);
t_matrix	get_tr_matrix_world2obj_plane(t_vector w_dir);
t_matrix	get_tr_matrix_world2obj_yup(t_vector w_dir);
t_matrix	get_tr_matrix_world2tangent(t_vector w_dir);


/********** img **********/
int			get_img(t_img *img, const char *img_path);
void		draw_img_test(t_data data, t_img img);
t_colorf	get_img_color(t_intersection_point intp, t_shape *shape, t_img img);
t_vector	get_bump_normal(t_intersection_point intp, t_shape *shape);


/********** calc_reflection **********/
t_colorf	calc_ambient_reflection(t_colorf ka, t_colorf Ia);
t_colorf calc_diffuse_reflection(const t_scene *scene, const t_ray *eye_ray,
								 t_intersection_point intp, t_shape *shape);
t_colorf	calc_perfect_reflection(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape);

t_colorf	calc_inflection_refraction(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape);

t_colorf	calc_specular_reflection(t_shape *shape, float nl_dot, t_light *light, t_vector dir_pos2light, t_vector eye_dir);


/********** raytrace **********/
int	recursive_raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level);
int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col);



/********** init **********/
void		scene_setting(t_scene *scene);
void		init_shape(t_shape *shape, t_shape_type st, ...);
void		init_material(t_material *mat,
				   float ambR, float ambG, float ambB,
				   float difR, float difG, float difB,
				   float speR, float speG, float speB,
				   float shns,
				   t_material_type type,
				   float refR, float refG, float refB,
				   float refraction_index,
				   char *texture_path, char *bump_path, bool is_checker);

void init_light(t_light *light, t_light_type lt,
				float px, float py, float pz,
				float dirx, float diry, float dirz,
				float illR, float illG, float illB,
				float angle);


/********** main **********/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif //MINIRT_H
