/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:28:12 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 12:40:04 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Rayと単一の物体との交差判定を行い、交差する場合にはその点への距離と位置とその位置での法線ベクトルを返す */
int	intersection_test(
		const t_shape *shape,
		const t_ray *ray,
		t_intersection_point *out_intp)
{

}

/*
 scene		【入力】交差判定の対象のscene_t構造体へのポインタ．
 ray		【入力】交差判定の対象のray_t構造体へのポインタ．
 max_dist	【入力】交差判定の最大距離．この距離より遠い位置で交点が見つかった場合は無視する．無限遠として処理する場合にはFLT_MAXを使用する．
 exit_once_found【入力】交差が一つでも見つかった場合に直ちに判定処理を終了するか否か．(非0で判定を終了．0で継続．)
 out_shape	【出力】交点が存在する最も近いshape_t構造体へのポインタ．NULLでもよい．
 out_intp	【出力】交点などの情報を出力するためのintersection_point_t構造体へのポインタ．NULLでもよい．
 戻り値 scene中に，rayが表す半直線上に交差する物体が存在しない場合はゼロを返す．そうでない場合は非ゼロを返す．
 */
int	get_nearest_shape(
		const t_scene *scene,
		const t_ray *ray,
		float max_dist,
		int exit_once_found,
		t_shape **out_shape,
		t_intersection_point *out_intp)
{

}


/*
 scene	【入力】交差判定の対象のscene_t構造体へのポインタ．
 ray	【入力】交差判定の対象のray_t構造体へのポインタ．
 out_col【出力】光線追跡の結果の色（輝度値）を格納するためのcolorf_t構造体へのポインタ．NULLは不可．
 戻り値	rayが表すレイと交差する物体が存在しない場合はゼロを返す．そうでない場合は非ゼロを返す．
 */
int raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{

}