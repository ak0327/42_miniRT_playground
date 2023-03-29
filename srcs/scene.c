/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:28:16 by takira            #+#    #+#             */
/*   Updated: 2023/03/29 21:20:33 by takira           ###   ########.fr       */
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
	scene->num_shapes_capacity = 7; /* 物体リストの最大格納数(自由に変更して良い) */
	scene->num_shapes = scene->num_shapes_capacity;	/* 物体リストに，実際に格納した物体の数 */

	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity);

//	/* 球 完全鏡面反射 */
//	init_shape(&scene->shapes[0], ST_SPHERE,
//			   -0.4f, -0.65f, 3.0f,	/* 球の中心位置 */
//			   0.35f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[0].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_PERFECT_REFLECTION, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */
//
//
//	/* 球 完全鏡面反射・屈折のみ */
//	init_shape(&scene->shapes[1], ST_SPHERE,
//			   0.5f, -0.65f, 2.0f,	/* 球の中心位置 */
//			   0.35f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.0f, 0.0f, 0.0f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_REFRACTION, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  1.51f);					/* 絶対屈折率 */
//
//
//	/* 白い床 */
//	init_shape(&scene->shapes[2], ST_PLANE,
//			   0.0f, -1.0f, 0.0f,		/* 平面が通る点の位置 */
//			   0.0f, 1.0f, 0.0f);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[2].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  1.0f, 1.0f, 1.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	/* 白い天井 */
//	init_shape(&scene->shapes[3], ST_PLANE,
//			   0.0f, 1.0f, 0.0f,		/* 平面が通る点の位置 */
//			   0.0f, -1.0f, 0.0f);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[3].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  1.0f, 1.0f, 1.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	/* 白い壁 */
//	init_shape(&scene->shapes[4], ST_PLANE,
//			   0.0f, 0.0f, 5.0f,		/* 平面が通る点の位置 */
//			   0.0f, 0.0f, -1.0f);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[4].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  1.0f, 1.0f, 1.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	/* 赤い壁 */
//	init_shape(&scene->shapes[5], ST_PLANE,
//			   -1.0f, 0.0f, 0.0f,		/* 平面が通る点の位置 */
//			   1.0f, 0.0f, 0.0f);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[5].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  1.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	/* 緑の壁 */
//	init_shape(&scene->shapes[6], ST_PLANE,
//			   1.0f, 0.0f, 0.0f,		/* 平面が通る点の位置 */
//			   -1.0f, 0.0f, 0.0f);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[6].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 1.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);



	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
//	init_shape(&scene->shapes[0], ST_PLANE,
//		   0.0, -1.0, 0.0,		/* 平面が通る点の位置 */
//		   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[0].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,								/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);


//	/* 三角形 */
//	init_shape(&scene->shapes[1], ST_TRIANGLE,
//			   1.0f, 1.0f, 0.0f,		/* 法線 */
//			   1.0f, 1.0f, 5.0f,		/* 位置 */
//			   3.0f, 1.2f, 5.0f,		/* p1 */
//			   -2.2f, 1.2f, 4.0f,		/* p2 */
//			   1.2f, 1.4f, 6.0f);		/* p3 */
//
//	init_material(&scene->shapes[1].material,
//				  0.5f, 0.5f, 0.5f,	/* 環境光係数(RGB)   */
//				  1.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	/* 三角形 */
//	init_shape(&scene->shapes[2], ST_TRIANGLE,
//			   -1.0f, 0.0f, 0.0f,		/* 法線 */
//			   -1.0f, 1.0f, 5.0f,		/* 位置 */
//			   -1.2f, 1.2f, 5.0f,		/* p1 */
//			   -1.2f, 1.2f, 5.0f,		/* p2 */
//			   -1.2f, 1.4f, 5.0f);		/* p3 */
//
//	init_material(&scene->shapes[2].material,
//				  0.5f, 0.5f, 0.5f,	/* 環境光係数(RGB)   */
//				  0.0f, 1.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  1.0f, 1.0f, 1.0f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_PERFECT_REFLECTION,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);


//	init_shape(&scene->shapes[0], ST_SPHERE,
//			   0.0f, 0.0f, 5.0f, /* 球の中心位置 */
//			   1.0f);    	/* 球の半径 */
//
//	init_material(&scene->shapes[0].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.69f, 0.00f, 0.00f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);




//	init_shape(&scene->shapes[1], ST_SPHERE,
//			   -2.0f, 0.0f, 10.0f, /* 球の中心位置 */
//			   0.5f);    	/* 球の半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_PERFECT_REFLECTION,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);

//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.69f, 0.00f, 0.00f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_PERFECT_REFLECTION,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);


//	init_shape(&scene->shapes[2], ST_CYLINDER,
//			   0.0f, 0.5f, 0.8f,	/* 法線ベクトル */
//			   0.0f, 0.0f, 10.0f,	/* 中心位置 */
//			   1.0f,				/* 高さ */
//			   0.5f);				/* 半径 */
//
//	init_material(&scene->shapes[2].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 1.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_PERFECT_REFLECTION,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[3], ST_CORN,
//			   -1.0f, -1.0f, 1.0f,	/* 法線ベクトル */
//			   1.5f, 0.0f, 10.0f,	/* 中心位置 */
//			   1.5f,				/* 高さ */
//			   0.5f);				/* 半径 */
//
//	init_material(&scene->shapes[3].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 1.0f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);





//	init_shape(&scene->shapes[0], ST_CYLINDER,
//			   0.0f, -1.0f, 0.0f,	/* 法線ベクトル */
//			   -1.0f, 0.5f, 5.0f,	/* 中心位置 */
//			   1.5f,				/* 高さ */
//			   0.75f);				/* 半径 */
//
//	init_material(&scene->shapes[0].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.69f, 0.0f, 0.69f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);



	init_shape(&scene->shapes[6], ST_SPHERE,
			   1.0f, -0.5f, 5.0f,	/* 球の中心位置 */
			   0.5f);    			/* 球の半径 */

	init_material(&scene->shapes[6].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_PERFECT_REFLECTION, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */

				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
				  0.7f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
				  8.0f,							/* 光沢度 */
				  MT_DEFAULT, 					/* マテリアルタイプ */
				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
				  0.0f);					/* 絶対屈折率 */



	init_shape(&scene->shapes[0], ST_CORN,
			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
			   -0.75f, 0.5f, 5.0f,	/* 中心位置 */
			   1.5f,				/* 高さ */
			   0.75f);				/* 半径 */

	init_material(&scene->shapes[0].material,
				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
				  0.69f, 0.0f, 0.69f,			/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  1.0f, 1.0f, 1.0f,
				  0.0f);
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.3f, 0.3f, 0.3f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_PERFECT_REFLECTION, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */



//	init_shape(&scene->shapes[0], ST_CYLINDER,
//			   0.0f, -1.0f, 0.0f,	/* 法線ベクトル */
//			   -0.75f, 0.5f, 5.0f,	/* 中心位置 */
//			   1.5f,				/* 高さ */
//			   0.5f);				/* 半径 */
//
////	init_shape(&scene->shapes[0], ST_CORN,
////			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
////			   -0.75f, 0.5f, 5.0f,	/* 中心位置 */
////			   1.5f,				/* 高さ */
////			   0.75f);				/* 半径 */
//
//	init_material(&scene->shapes[0].material,
////				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
////				  0.69f, 0.0f, 0.69f,			/* 拡散反射係数(RGB) */
////				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
////				  8.0f,
////				  MT_DEFAULT,
////				  1.0f, 1.0f, 1.0f,
////				  0.0f);
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
//				  0.0f,							/* 光沢度 */
//				  MT_PERFECT_REFLECTION, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */

	init_shape(&scene->shapes[1], ST_CORN,
			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
			   0.0f, 0.5f, 10.0f,	/* 中心位置 */
			   1.5f,				/* 高さ */
			   0.75f);				/* 半径 */

	init_material(&scene->shapes[1].material,
				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
				  0.0f, 0.69f, 0.69f,			/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  0.0f);



	init_shape(&scene->shapes[2], ST_CORN,
			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
			   1.0f, 0.5f, 15.0f,	/* 中心位置 */
			   1.5f,				/* 高さ */
			   0.75f);				/* 半径 */

	init_material(&scene->shapes[2].material,
				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
				  0.0f, 0.0f, 0.69f,			/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  0.0f);



	init_shape(&scene->shapes[3], ST_CORN,
			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
			   2.0f, 0.5f, 20.0f,	/* 中心位置 */
			   1.5f,				/* 高さ */
			   0.75f);				/* 半径 */

	init_material(&scene->shapes[3].material,
				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
				  0.0f, 0.69f, 0.0f,			/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  0.0f);



	init_shape(&scene->shapes[4], ST_CORN,
			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
			   3.0f, 0.5f, 25.0f,	/* 中心位置 */
			   1.5f,				/* 高さ */
			   0.75f);				/* 半径 */

	init_material(&scene->shapes[4].material,
				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
				  0.69f, 0.0f, 0.0f,			/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  0.0f);



	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
	init_shape(&scene->shapes[5], ST_PLANE,
			   0.0, -1.0, 0.0,		/* 平面が通る点の位置 */
			   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */

	init_material(&scene->shapes[5].material,
				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,								/* 光沢度 */
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  0.0f);



//	size_t	i = 1;
//	while (i < scene->num_shapes_capacity)
//	{
//		init_shape(&scene->shapes[i], ST_SPHERE,
//				   rand_f(-5.0f, 5.5f), rand_f(0.0f, 5.0f), rand_f(0.0f, 20.0f),	/* 球の中心位置 */
//				   rand_f(0.25f, 1.5f));			/* 球の半径 */
//
//		init_material(&scene->shapes[i].material,
//					  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//					  rand_f(0.5f, 1.0f), rand_f(0.5f, 1.0f), rand_f(0.5f, 1.0f),		/* 拡散反射係数(RGB) */
//					  rand_f(0.3f, 0.5f), rand_f(0.3f, 0.5f), rand_f(0.3f, 0.5f),		/* 鏡面反射率(RGB)   */
//					  8.0f,								/* 光沢度 */
//					  MT_DEFAULT,
//					  0.0f, 0.0f, 0.0f,
//					  0.0f);
//		i++;
//	}


	/* ************************************************** */
	/*                   光源の設定                        */
	/* ************************************************** */
	/* 環境光の強さ */
	/* colorf_t構造体に値を設定する場合は，このように SET_COLORマクロを使うことができる． */
	SET_COLOR(scene->ambient_illuminance, 0.1, 0.1, 0.1);

	scene->num_lights_capacity = 2;
	scene->num_lights = scene->num_lights_capacity;
	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights_capacity);

	/* outside */
//	init_light(&scene->lights[0], LT_POINT,
//			   -5.0f, 5.0f, -5.0f, /* 点光源の位置 */
//			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */

	init_light(&scene->lights[0], LT_POINT,
			   10.0f, 5.0f, -5.0f, /* 点光源の位置 */
			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */


	/* 部屋 */
//	init_light(&scene->lights[0], LT_POINT,
//			   0.0f, 0.9f, 2.5f, /* 点光源の位置 */
//			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */


	/* 平行光源の場合 */
	init_light(&scene->lights[1], LT_DIRECTIONAL,
		   0.0f, -1.0f, 0.0f,  /*平行光源の方向ベクトル */
		   1.0f, 1.0f, 1.0f);  /* 平行光源の照度(色)*/

	scene->global_refraction_index = 1.0f;

}
