/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/03/12 20:44:57 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{
	/*1. 視線方向(eye_ray)の方向でもっとも近い物体を探す。*/
	int						res;
	t_shape					*shape;
	t_intersection_point	intp;

	res = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);

	/*視線方向に物体があった場合*/
	if (res)
	{
		t_colorf col = {0,0,0}; /*色の計算結果を入れる変数*/

		/*2. 環境光の強さを計算してcolに入れる。 */

		for(/*3. すべての光源について処理する*/)
		{
			/*4. 入射ベクトルを計算する（点光源の場合と平行光源の場合）。*/

			/*5. 拡散反射光を計算してcolに足し合わせる。*/

			/*6. 鏡面反射光を計算してcolに足し合わせる*/
		}

		*out_col = col;
		return (1);
	}
	return (0);
}

