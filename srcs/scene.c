/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:28:16 by takira            #+#    #+#             */
/*   Updated: 2023/03/13 10:31:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void scene_setting(t_scene *scene)
{
	/* ************************************************** */
	/*                    物体の設定                       */
	/* ************************************************** */
	scene->num_shapes_capacity = 16; /* 物体リストの最大格納数(自由に変更して良い) */

	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity); /* メモリ確保 */


	/* 物体の初期化 ... init_shape()関数を使う．第一引数は初期化するshape_t構造体のポインタ．*/
	/* 球の場合：第二引数にST_SHAPEを渡す．この場合，追加で4つの実数を渡す． */
	init_shape(&scene->shapes[0], ST_SPHERE,
			   0.0, 0.0, 5.0,	/* 球の中心位置 */
			   1.0);			/* 球の半径 */

	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
	init_shape(&scene->shapes[1], ST_PLANE,
		   0.0, -1.0, 0.0,		/* 平面が通る点の位置 */
		   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */

	/* 補足：vector_t構造体に値を設定する場合は以下のように，SET_VECTORマクロを使うことができる． */
	/* SET_VECTOR(scene->shapes[0].data.sphere.center, 0, 5, 5); */

	/* マテリアルの初期化 ... init_material()関数を使う．*/
	/* 第一引数は初期化するmaterial_t構造体のポインタ． */
	init_material(&scene->shapes[0].material,
				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
				  0.69f, 0.00f, 0.00f,		/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f);								/* 光沢度 */

	init_material(&scene->shapes[1].material,
				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f);								/* 光沢度 */

	scene->num_shapes = 2;	/* 物体リストに，実際に格納した物体の数 */


	/* ************************************************** */
	/*                   光源の設定                        */
	/* ************************************************** */
	/* 環境光の強さ */
	/* colorf_t構造体に値を設定する場合は，このように SET_COLORマクロを使うことができる． */
	SET_COLOR(scene->ambient_illuminance, 0.1, 0.1, 0.1);

	scene->num_lights_capacity = 16; /* 光源リストの最大格納数(自由に変更して良い) */
	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights_capacity); /* メモリ確保 */

	/* 光源の初期化 ... init_light()関数を使う． 第一引数は初期化するlight_t構造体のポインタ．*/

	/* 点光源の場合 */
	init_light(&scene->lights[0], LT_POINT,
			   -5.0f, 5.0f, -5.0f, /* 点光源の位置 */
			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */

	/* 平行光源の場合 */
	/*
	init_light(&scene->lights[0], LT_DIRECTIONAL,
		   0.0, -1.0, 0.0,  平行光源の方向ベクトル
		   1.0, 1.0, 1.0);  平行光源の照度(色)
	*/

	scene->num_lights = 1; /* 光源リストに，実際に格納した光源の数 */
	/* 光源数を変えた場合はそれに合わせて書き換えること． */
	/* 光源リストの先頭 num_lights 個は初期化されている必要がある． */
}
