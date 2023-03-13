/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:28:16 by takira            #+#    #+#             */
/*   Updated: 2023/03/13 10:57:59 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	rand_f(float under, float upper)
{
	return (under + (upper - under) * (float)rand()/RAND_MAX);
}

void scene_setting(t_scene *scene)
{
	/* ************************************************** */
	/*                    物体の設定                       */
	/* ************************************************** */
	scene->num_shapes_capacity = 100; /* 物体リストの最大格納数(自由に変更して良い) */
	scene->num_shapes = scene->num_shapes_capacity;	/* 物体リストに，実際に格納した物体の数 */

	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity); /* メモリ確保 */

	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
	init_shape(&scene->shapes[0], ST_PLANE,
		   0.0, -1.0, 0.0,		/* 平面が通る点の位置 */
		   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */

	init_material(&scene->shapes[0].material,
				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f);								/* 光沢度 */

//	init_shape(&scene->shapes[1], ST_SPHERE,
//			   0.0f, 0.0f, 5.0f, /* 球の中心位置 */
//			   1.0f);    	/* 球の半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.01f, 0.01f, 0.01f,  /* 環境光係数(RGB)   */
//				  0.69f, 0.00f, 0.00f,  /* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,  /* 鏡面反射率(RGB)   */
//				  8.0f); /* 光沢度 */				/* 光沢度 */

	size_t	i = 1;
	while (i < scene->num_shapes_capacity)
	{
		init_shape(&scene->shapes[i], ST_SPHERE,
				   rand_f(-2.5f, 2.5f), rand_f(0.0f, 2.0f), rand_f(0.0f, 20.0f),	/* 球の中心位置 */
				   rand_f(0.25f, 0.5f));			/* 球の半径 */

		init_material(&scene->shapes[i].material,
					  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
					  rand_f(0.5f, 1.0f), rand_f(0.5f, 1.0f), rand_f(0.5f, 1.0f),		/* 拡散反射係数(RGB) */
					  rand_f(0.3f, 0.5f), rand_f(0.3f, 0.5f), rand_f(0.3f, 0.5f),		/* 鏡面反射率(RGB)   */
					  8.0f);								/* 光沢度 */
		i++;
	}


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
