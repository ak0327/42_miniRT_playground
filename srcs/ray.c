/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/04/06 18:27:33 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recursive_raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level, t_img img);

static t_colorf	calc_perfect_reflection_color(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_vector	eye_dir;
	t_vector	n_dir;			// 法線ベクトル
	float		vn_dot;
	t_vector	ref_dir;
	t_vector	inv_eye_dir;

	t_ray		re_ray;		// 反射ray,
	t_colorf	re_color;	// 反射光の輝度

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	n_dir = normalize_vec(&intp.normal);
	eye_dir = normalize_vec(&eye_ray->direction);

	/* 視線ベクトルの逆ベクトルの計算 */
	inv_eye_dir = normalize_vec_inv(&eye_dir);

	/* 視線ベクトルの逆ベクトルと法線ベクトルの内積 */
	vn_dot = dot(&inv_eye_dir, &n_dir);

	/* vn_dot <= 0 のとき */
	if (vn_dot <= EPSILON)
		return (color);

	/* 視線ベクトルの正反射ベクトルを計算 */
	ref_dir = vec_calc(2.0f * vn_dot, &n_dir, -1, &inv_eye_dir);
	normalize(&ref_dir);

	/* 正反射方向のrayを計算 */
	re_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &ref_dir);
	re_ray.direction = ref_dir;

	re_color = *out_col;
	recursive_raytrace(scene, &re_ray, &re_color, recursion_level + 1, img);

	/* 完全鏡面反射を計算 */
	color = colorf_mul(&color, 1.0f, &shape->material.reflect_ref, 1.0f, &re_color);
	return (color);
}

static t_colorf	calc_inflection_refraction_color(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape, t_img img)
{
	float		eta_1;			// 物質1（屈折前）の絶対屈折率
	float		eta_2;			// 物質2（屈折後）の絶対屈折率
	float		eta_r;			// 一時変数eta_r
	t_vector	re_dir, fe_dir;	// 反射方向、屈折方向
	t_ray		fe_ray;			// 屈折ray
	t_colorf	fe_color;		// 屈折光の輝度
	float		cos_theta1, cos_theta2;
	float		rho_p, rho_s;	// p偏光反射率, s偏光反射率
	float		cr, ct;			// 反射率, 透過率
	float		omega;			// 一時変数

	t_colorf	color;
	t_vector	eye_dir;
	t_vector	n_dir;			// 法線ベクトル
	float		vn_dot;
	t_vector	inv_eye_dir;

	t_ray		re_ray;		// 反射ray,
	t_colorf	re_color;	// 反射光の輝度

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	n_dir = normalize_vec(&intp.normal);
	eye_dir = normalize_vec(&eye_ray->direction);

	/* 視線ベクトルの逆ベクトルの計算 */
	inv_eye_dir = normalize_vec_inv(&eye_dir);

	/* 視線ベクトルの逆ベクトルと法線ベクトルの内積 */
	vn_dot = dot(&inv_eye_dir, &n_dir);

	if (vn_dot >= EPSILON)
	{
		eta_1 = scene->global_refraction_index;
		eta_2 = shape->material.refraction_index;
	}
	else // 物体の裏側から入射した場合
	{
		/* 法線ベクトルをひっくり返し内積を計算しなおす */
		n_dir = normalize_vec_inv(&n_dir);
		vn_dot = dot(&inv_eye_dir, &n_dir);

		/* 屈折率1,2を入れ替える */
		eta_1 = shape->material.refraction_index;
		eta_2 = scene->global_refraction_index;
	}

	eta_r = eta_2 / eta_1;

	/* cos(theta1), cos(theta2)の計算 */
	cos_theta1 = vn_dot;
	cos_theta2 = eta_1 / eta_2 * sqrtf(SQR(eta_r) - (1.0f - SQR(cos_theta1)));

	/* 一時変数omegaの計算 */
	omega = eta_r * cos_theta2 - cos_theta1;


	/* 完全鏡面反射率、透過率の計算 */
	rho_p = (eta_r * cos_theta1 - cos_theta2) / ((eta_r * cos_theta1 + cos_theta2));
	rho_s = -1.0f * omega / (cos_theta1 + eta_r * cos_theta2);
	cr = 0.5f * (SQR(rho_p) + SQR(rho_s));
	ct = 1.0f - cr;


	/* 正反射方向ベクトルの計算 */
	re_dir = vec_calc(2.0f * vn_dot, &n_dir, -1.0f, &inv_eye_dir);
	normalize(&re_dir);

	/* 正反射方向のレイの始点を計算 */
	re_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &re_dir);
	re_ray.direction = re_dir;


	/* 屈折方向のレイの始点を計算 */
	fe_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &fe_dir);
	fe_ray.direction = fe_dir;

	/* 屈折方向ベクトルの計算 */
	fe_dir = vec_calc(eta_1 / eta_2, &eye_dir, eta_1 / eta_2 * omega, &n_dir);
	normalize(&fe_dir);


	/* colorの初期化 */
	re_color = *out_col;
	fe_color = *out_col;

	/* 再帰呼び出し（反射） */
	recursive_raytrace(scene, &re_ray, &re_color, recursion_level + 1, img);
	/* 再帰呼び出し（屈折） */
	recursive_raytrace(scene, &fe_ray, &fe_color, recursion_level + 1, img);

	/* 完全鏡面反射、屈折光を計算 */
	color = colorf_mul(&color, 1.0f, &shape->material.reflect_ref, cr, &re_color);
	color = colorf_mul(&color, 1.0f, &shape->material.reflect_ref, ct, &fe_color);
	return (color);
}

static t_colorf calc_light_color(const t_scene *scene, const t_ray *eye_ray,
								 t_intersection_point intp, t_shape *shape, t_img img)
{
	t_colorf	color;
	t_colorf	checker_col;
	t_colorf	img_col;

	size_t		i;
	t_light		*light;
	t_vector	light_dir; 	// 入射ベクトル
	float		nl_dot;		// 法線ベクトルと入射ベクトルの内積
	t_vector	ref_dir;
	float		vr_dot;
	float		vr_dot_pow;

	t_vector	inv_eye_dir;

	int 		shadow_int_res;
	t_ray		shadow_ray;
	float		dist;
	t_vector	vec_pi_to_light;

	t_vector	normal = intp.normal;


//	if (shape->type == ST_PLANE)
//		normal = get_bump_normal(scene, eye_ray, intp, shape, img);
	if (shape->type == ST_SPHERE)
		normal = get_bump_normal(scene, eye_ray, intp, shape, img);

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	inv_eye_dir = normalize_vec_inv(&eye_ray->direction);

	i = 0;
	while (i < scene->num_lights)
	{
		/* 入射ベクトル light_dir を計算する（点光源の場合と平行光源の場合） */
		light = &scene->lights[i];
		i++;

		if (light->type == LT_POINT || light->type == LT_SPOT)
			light_dir = sub(&light->position, &intp.position);
		else
			light_dir = light->direction;	// 平行光源

		normalize(&light_dir);
		nl_dot = CLAMP(dot(&normal, &light_dir), 0, 1);

		/* shadow_rayを計算 */
		shadow_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &light_dir);
		shadow_ray.direction = light_dir;
		if (light->type == LT_POINT)
		{
			vec_pi_to_light = sub(&light->position, &intp.position);
			dist = norm(&vec_pi_to_light) - EPSILON;
		}
		else
			dist = FLT_MAX;

		shadow_int_res = get_nearest_shape(scene, &shadow_ray, dist, 1, NULL, NULL);

		/* shadow_rayが物体に遮られた場合 */
		if (shadow_int_res)
			continue ;

		/* shadow_rayが物体に遮られなかった場合 */
		/* 拡散反射光 diffuse を計算してcolに足し合わせる */

//		checker_col = get_checker_color(scene, eye_ray, intp, shape);
//		color = colorf_add(&color, &checker_col);

//		img_col = get_img_color(scene, eye_ray, intp, shape, img);
//		color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&img_col);

		// 一時的にPLANEの反射を無効化
//		if (shape->type == ST_PLANE)
//			return (color);

		if (light->type == LT_SPOT)
		{
			t_vector	light_to_pos = normalize_vec_inv(&light_dir);
			float		alpha = acosf(dot(&light_to_pos, &light->direction));
			if (alpha <= light->angle / 2.0f * (float)M_PI / 180.0f)
			{
				color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&light->illuminance);

				if (nl_dot > EPSILON)
				{
					/* 正反射ベクトルの計算 */
					ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &light_dir);
					normalize(&ref_dir);

					vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
					vr_dot_pow = powf(vr_dot, shape->material.shininess);

					/* 鏡面反射光の計算 */
					color = colorf_mul(&color, 1.0f, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
				}
			}
		}
		else
		{
			color = colorf_mul(&color, 1.0f, &shape->material.diffuse_ref, nl_dot,&light->illuminance);

			/* 鏡面反射光 specular を計算してcolに足し合わせる */
			if (nl_dot > EPSILON)
			{
				/* 正反射ベクトルの計算 */
				ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &light_dir);
				normalize(&ref_dir);

				vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0, 1);
				vr_dot_pow = powf(vr_dot, shape->material.shininess);

				/* 鏡面反射光の計算 */
				color = colorf_mul(&color, 1.0f, &shape->material.specular_ref, vr_dot_pow, &light->illuminance);
			}
		}
	}
	return (color);
}

int	recursive_raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level, t_img img)
{
	int						intersect_result;	// 交差判定の結果
	t_shape					*shape;		// 交差した物体へのポインタ
	t_intersection_point	intp;		// 交点

	t_colorf				color;
	t_colorf				perfect_reflect_color;
	t_colorf				inflection_refraction_color;
	t_colorf				light_color;

	if (recursion_level > MAX_RECURSION)
		return (0);

	intersect_result = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);

	/* 視線方向に物体がなかった場合 */
	if (!intersect_result)
		return (0);

	/* 環境光Laを計算しcolに入れる */
	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	color = colorf_mul(&color, 1.0f, &scene->ambient_illuminance, 1.0f, &shape->material.ambient_ref);

	if (shape->material.type == MT_PERFECT_REFLECTION)
	{
		/* 完全鏡面反射 */
		perfect_reflect_color = calc_perfect_reflection_color(scene, eye_ray,
															  out_col,
															  recursion_level,
															  intp, shape, img);
		color = colorf_add(&color, &perfect_reflect_color);
	}
	else if (shape->material.type == MT_REFRACTION)
	{
		/* 屈折 */
		inflection_refraction_color = calc_inflection_refraction_color(scene, eye_ray, out_col, recursion_level, intp, shape, img);
		color = colorf_add(&color, &inflection_refraction_color);
	}

	light_color = calc_light_color(scene, eye_ray,  intp, shape, img);
	color = colorf_add(&color, &light_color);

	*out_col = color;
	return (1);
}

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, t_img img)
{
	return (recursive_raytrace(scene, eye_ray, out_col, 0, img));
}
