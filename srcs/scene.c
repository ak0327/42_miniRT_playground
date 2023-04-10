/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:28:16 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 16:13:42 by takira           ###   ########.fr       */
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
//	scene->num_shapes_capacity = 17; /* 物体リストの最大格納数(自由に変更して良い) */
//	scene->num_shapes = scene->num_shapes_capacity;	/* 物体リストに，実際に格納した物体の数 */
//
//	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity);

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








/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                          corn & cylinder  using checker ここから                        */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

//	scene->num_shapes_capacity = 17; /* 物体リストの最大格納数(自由に変更して良い) */
//	scene->num_shapes = scene->num_shapes_capacity;	/* 物体リストに，実際に格納した物体の数 */
//
//	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity);
//
//
//	init_shape(&scene->shapes[0], ST_CORN,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   -7.5f, 15.0f, 30.0f,	/* 中心位置 */
//			   15.0f,				/* 高さ */
//			   7.5f);				/* 半径 */
//
//	init_material(&scene->shapes[0].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.69f, 0.0f, 0.69f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[1], ST_CORN,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   0.0f, 15.0f, 50.0f,	/* 中心位置 */
//			   15.0f,				/* 高さ */
//			   7.5f);				/* 半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.69f, 0.69f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//
//	init_shape(&scene->shapes[2], ST_CORN,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   10.0f, 15.0f, 70.0f,	/* 中心位置 */
//			   15.0f,				/* 高さ */
//			   7.5f);				/* 半径 */
//
//	init_material(&scene->shapes[2].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.69f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//
//	init_shape(&scene->shapes[3], ST_CORN,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   20.0f, 15.0f, 90.0f,	/* 中心位置 */
//			   15.0f,				/* 高さ */
//			   7.5f);				/* 半径 */
//
//	init_material(&scene->shapes[3].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.69f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//
//	init_shape(&scene->shapes[4], ST_CORN,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   30.0f, 15.0f, 110.0f,	/* 中心位置 */
//			   15.0f,				/* 高さ */
//			   7.5f);				/* 半径 */
//
//	init_material(&scene->shapes[4].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.69f, 0.0f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//
//
//	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
//	init_shape(&scene->shapes[5], ST_PLANE,
//			   0.0, 0.0, 0.0,		/* 平面が通る点の位置 */
//			   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[5].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,								/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[6], ST_SPHERE,
//			   15.0f, 4.0f, 15.0f,	/* 球の中心位置 */
//			   4.0f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[6].material,
////				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
////				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
////				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
////				  0.0f,							/* 光沢度 */
////				  MT_PERFECT_REFLECTION, 					/* マテリアルタイプ */
////				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
////				  0.0f);					/* 絶対屈折率 */
//
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.7f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_DEFAULT, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */
//
//
//	init_shape(&scene->shapes[7], ST_CYLINDER,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   0.0f, 0.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[7].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.7f, 0.0f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[8], ST_CYLINDER,
//			   1.5f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   0.0f, 10.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[8].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.7f, 0.0f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[9], ST_CYLINDER,
//			   1.0f, 0.0f, 0.0f,	/* 法線ベクトル */
//			   18.0f, 3.0f, 0.0f,	/* 中心位置 */
//			   3.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[9].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.7f, 0.7f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[10], ST_CYLINDER,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   -10.0f, 0.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[10].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.7f, 0.7f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[11], ST_CYLINDER,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   10.0f, 0.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[11].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.7f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[12], ST_CYLINDER,
//			   2.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   10.0f, 10.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[12].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.7f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[13], ST_CYLINDER,
//			   0.5f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   -10.0f, 10.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[13].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.7f, 0.7f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[14], ST_SPHERE,
//			   30.0f, 7.5f, 20.0f,	/* 球の中心位置 */
//			   7.5f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[14].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.7f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_DEFAULT, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */
//
//
//
//	init_shape(&scene->shapes[15], ST_CORN,
//			   1.0f, 0.0f, 0.0f,	/* 法線ベクトル */
//			   0.0f, 15.0f, 50.0f,	/* 中心位置 */
//			   15.0f,				/* 高さ */
//			   7.5f);				/* 半径 */
//
//	init_material(&scene->shapes[15].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.0f, 0.69f, 0.69f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[16], ST_CYLINDER,
//			   -0.5f, 0.0f, 1.0f,	/* 法線ベクトル */
//			   27.0f, 3.0f, 0.0f,	/* 中心位置 */
//			   5.0f,				/* 高さ */
//			   3.0f);				/* 半径 */
//
//	init_material(&scene->shapes[16].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.7f, 0.7f, 0.0f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);


//	scene->num_lights_capacity = 1;
//	scene->num_lights = scene->num_lights_capacity;
//	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights_capacity);

	/* outside */
//	init_light(&scene->lights[0], LT_POINT,
//			   50.0f, 50.0f, -50.0f, /* position */
//			   0.0f, 0.0f, 0.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */


/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                          corn & cylinder  using checker ここまで                        */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */










/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
/*                          spotlight   ここから                                           */
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */

//	scene->num_shapes_capacity = 2; /* 物体リストの最大格納数(自由に変更して良い) */
//	scene->num_shapes = scene->num_shapes_capacity;	/* 物体リストに，実際に格納した物体の数 */
//
//	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity);
//
//	init_shape(&scene->shapes[0], ST_PLANE,
//			   0.0, 0.0, 0.0,		/* 平面が通る点の位置 */
//			   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[0].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,								/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//		init_shape(&scene->shapes[1], ST_SPHERE,
//			   0.0f, 5.0f, 10.0f,	/* 球の中心位置 */
//			   5.0f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.7f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_DEFAULT, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */
//
//
//
//	SET_COLOR(scene->ambient_illuminance, 0.1, 0.1, 0.1);
//	scene->num_lights_capacity = 4;
//	scene->num_lights = scene->num_lights_capacity;
//	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights_capacity);
//	scene->global_refraction_index = 1.0f;
//
//	init_light(&scene->lights[0], LT_POINT,
//			   50.0f, 50.0f, -50.0f, /* position */
//			   0.0f, 0.0f, 0.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 1.0f, 1.0f,
//			   60.0f);   /* 点光源の照度(色) */
//
//
//	init_light(&scene->lights[1], LT_SPOT,
//			   00.0f, 50.0f, 10.0f,	/* position */
//			   0.0f, -1.0f, 0.0f,	/* direction(do not use LT_POINT) */
//			   0.0f, 1.0f, 0.0f,	/* 照度(色) */
//			   35.0f);					/* projection angle of spotlight */
//
//
//	init_light(&scene->lights[2], LT_SPOT,
//			   -30.0f, 5.0f, -20.0f,	/* position */
//			   1.0f, -0.2f, 1.0f,	/* direction(do not use LT_POINT) */
//			   0.0f, 0.0f, 1.0f,	/* 照度(色) */
//			   35.f);						/* projection angle of spotlight */
//
//	init_light(&scene->lights[3], LT_SPOT,
//			   30.0f, 5.0f, -20.0f,	/* position */
//			   -1.0f, -0.2f, 1.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 0.0f, 0.0f,	/* 照度(色) */
//			   35.f);						/* projection angle of spotlight */

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                          spotlight ここまで                                             */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */





/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
/*                          bump mapping   ここから                                        */
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */

	scene->num_shapes_capacity = 6; /* 物体リストの最大格納数(自由に変更して良い) */
	scene->num_shapes = scene->num_shapes_capacity;	/* 物体リストに，実際に格納した物体の数 */

	scene->shapes = (t_shape *)malloc(sizeof(t_shape) * scene->num_shapes_capacity);

	init_shape(&scene->shapes[0], ST_PLANE,
			   0.0, 0.0, 0.0,		/* 平面が通る点の位置 */
			   0.0, 1.0, 0.0);		/* 平面の法線ベクトル */

	init_material(&scene->shapes[0].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
				  0.7f, 0.7f, 0.7f,		/* 拡散反射係数(RGB) */
				  0.10f, 0.10f, 0.10f,		/* 鏡面反射率(RGB)   */
				  1.0f,								/* 光沢度 */
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  0.0f,
//				  "./img/cat.ppm",
//				  (char *)NULL,
				  (char *)NULL,
				  (char *)NULL,
				  true);

//	init_shape(&scene->shapes[1], ST_SPHERE,
//			   0.0f, 10.0f, 0.0f,	/* 球の中心位置 */
//			   10.0f);    			/* 球の半径 */
//
//	init_shape(&scene->shapes[1], ST_SPHERE,
//			   0.0f, 100.0f, 0.0f,	/* 球の中心位置 */
//			   100.0f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
//				  0.5f, 0.5f, 0.5f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_DEFAULT, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f);					/* 絶対屈折率 */


//	init_shape(&scene->shapes[1], ST_CYLINDER,
//			   0.0f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   0.0f, 0.0f, 0.0f,	/* 中心位置 */
//			   200.0f,				/* 高さ */
//			   100.0f);				/* 半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.5f, 0.5f, 0.5f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);
//
//
//	init_shape(&scene->shapes[2], ST_CYLINDER,
//			   0.5f, 1.0f, 0.0f,	/* 法線ベクトル */
//			   250.0f, 100.0f, 0.0f,	/* 中心位置 */
//			   200.0f,				/* 高さ */
//			   100.0f);				/* 半径 */
//
//	init_material(&scene->shapes[2].material,
//				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
//				  0.5f, 0.5f, 0.5f,			/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,
//				  MT_DEFAULT,
//				  1.0f, 1.0f, 1.0f,
//				  0.0f);




// ******************************
	init_shape(&scene->shapes[1], ST_CORN,
			   -0.2f, 1.0f, 0.0f,	/* 法線ベクトル */
			   -150.0f, 20.0f, 0.0f,	/* 中心位置 */
			   130.0f,				/* 高さ */
			   65.0f);				/* 半径 */

	init_material(&scene->shapes[1].material,
				  0.01f, 0.01f, 0.01f, 	/* 環境光係数(RGB)   */
				  0.8f, 0.8f, 0.8f,			/* 拡散反射係数(RGB) */
				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  1.0f, 1.0f, 1.0f,
				  8.0f,
				  (char *)NULL,
				  (char *)NULL,
				  true);


	init_shape(&scene->shapes[2],  ST_CYLINDER,
			   0.0f, 1.0f, 0.3f,	/* 法線ベクトル */
			   100.0f, 50.0f, 0.0f,	/* 中心位置 */
			   130.0f,				/* 高さ */
			   50.0f);				/* 半径 */

	init_material(&scene->shapes[2].material,
				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
				  0.0f, 0.5f, 0.0f,		/* 拡散反射係数(RGB) */
				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
				  8.0f,
				  MT_DEFAULT,
				  1.0f, 1.0f, 1.0f,
				  8.0f,
//				  "./img/cat.ppm",
				  (char *)NULL,
				  "./img/normalmap_example.ppm",
				  false);


	init_shape(&scene->shapes[3], ST_SPHERE,
			   0.0f, 50.0f, -150.0f,	/* 球の中心位置 */
			   50.0f);    			/* 球の半径 */

	init_material(&scene->shapes[3].material,
				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
				  0.5f, 0.5f, 0.0f,		/* 拡散反射係数(RGB) */
				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
				   8.0f,							/* 光沢度 */
				  MT_DEFAULT, 					/* マテリアルタイプ */
				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
				  8.0f,
//				  "./img/cat.ppm",
//				  (char *)NULL,
//				  "./img/1k_earth.ppm",
//				  "./img/1k_earth_normal.ppm",
				  (char *)NULL,
				  "./img/normalmap_example.ppm",
				  false);					/* 絶対屈折率 */


	init_shape(&scene->shapes[4], ST_PLANE,
			   -200.0f, 0.0f, 200.0f,		/* 平面が通る点の位置 */
			   1.0f, 1.0f, -1.0f);		/* 平面の法線ベクトル */
//			   -1.0f, -1.0f, 1.0f);		/* 平面の法線ベクトル */

	init_material(&scene->shapes[4].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
				  0.7f, 0.7f, 0.7f,		/* 拡散反射係数(RGB) */
				  0.10f, 0.10f, 0.10f,		/* 鏡面反射率(RGB)   */
				  1.0f,								/* 光沢度 */
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  8.0f,
//				  "./img/cat.ppm",
				  (char *)NULL,
				  (char *)NULL,
				  true);



	init_shape(&scene->shapes[5], ST_PLANE,
			   400.0f, 0.0f, 200.0f,		/* 平面が通る点の位置 */
//			   -1.0f, 0.0f, -0.2f);		/* 平面の法線ベクトル */
			   1.0f, 0.0f, 0.2);		/* 平面の法線ベクトル */

	init_material(&scene->shapes[5].material,
//				  0.0f, 0.0f, 0.0f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.0f, 0.0f, 0.0f,		/* 鏡面反射率(RGB)   */
				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
				  0.7f, 0.7f, 0.7f,		/* 拡散反射係数(RGB) */
				  0.10f, 0.10f, 0.10f,		/* 鏡面反射率(RGB)   */
				  1.0f,								/* 光沢度 */
				  MT_DEFAULT,
				  0.0f, 0.0f, 0.0f,
				  8.0f,
//				  "./img/cat.ppm",
//				  "./img/normalmap_example.ppm",
				  (char *)NULL,
				  (char *)NULL,
				  true);

// ******************************

//	init_shape(&scene->shapes[0], ST_PLANE,
//			   0.0f, 0.0f, 0.0f,		/* 平面が通る点の位置 */
//			   0.0f, 0.0f, -1.0f);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[0].material,
//				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
//				  0.7f, 0.7f, 0.7f,		/* 拡散反射係数(RGB) */
//				  0.10f, 0.10f, 0.10f,		/* 鏡面反射率(RGB)   */
//				  1.0f,								/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f,
//				  "./img/cat.ppm",
//				  (char*)NULL,
//				  true);
//
//
//
//	init_shape(&scene->shapes[1], ST_SPHERE,
//			   0.0f, -50.0f, -150.0f,	/* 球の中心位置 */
//			   50.0f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[1].material,
//				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
//				  0.5f, 0.0f, 0.0f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				   8.0f,							/* 光沢度 */
//				  MT_DEFAULT, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f,
//				  (char *)NULL,
//				  "./img/normalmap_example.ppm",
//				  false);					/* 絶対屈折率 */
//
//
//	init_shape(&scene->shapes[2], ST_SPHERE,
//			   0.0f, 50.0f, 150.0f,	/* 球の中心位置 */
//			   50.0f);    			/* 球の半径 */
//
//	init_material(&scene->shapes[2].material,
//				  0.1f, 0.1f, 0.1f,	/* 環境光係数(RGB)   */
//				  0.0f, 0.0f, 0.5f,		/* 拡散反射係数(RGB) */
//				  0.3f, 0.3f, 0.3f,		/* 鏡面反射率(RGB)   */
//				  8.0f,							/* 光沢度 */
//				  MT_DEFAULT, 					/* マテリアルタイプ */
//				  1.0f, 1.0f, 1.0f,		/* 完全鏡面反射係数(RGB) */
//				  0.0f,
//				  (char *)NULL,
//				  (char *)NULL,
//				  false);					/* 絶対屈折率 */




	SET_COLOR(scene->ambient_illuminance, 0.1f, 0.1f, 0.1f);
	scene->num_lights_capacity = 1;
	scene->num_lights = scene->num_lights_capacity;
	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights_capacity);

//	init_light(&scene->lights[0], LT_POINT,
//			   30.0f, 50.0f, -30.0f,	/* position */
//			   -1.0f, -1.0f, 1.0f,	/* direction(do not use LT_POINT) */
//			   0.5f, 0.5f, 0.5f,	/* color */
//			   70.0f);					/* angle */

	// cylinder
	init_light(&scene->lights[0], LT_POINT,
			   -200.0f, 500.0f, -300.0f,	/* position */
			   0.0f, 1.0f, 0.0f,	/* direction(do not use LT_POINT) */
			   0.7f, 0.7f, 0.7f,	/* color */
			   70.0f);					/* angle */




	// sphere from up
//	init_light(&scene->lights[0], LT_POINT,
//			   100.0f, 300.0f, -100.0f,	/* position */
//			   0.0f, 1.0f, 0.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 1.0f, 1.0f,	/* color */
//			   70.0f);					/* angle */

//	init_light(&scene->lights[0], LT_DIRECTIONAL,
//			   0.0f, 500.0f, 0.0f,	/* position */
//			   0.0f, -1.0f, 0.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 1.0f, 1.0f,	/* color */
//			   70.0f);					/* angle */


/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                         bump mapping ここまで                                           */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */














//	init_light(&scene->lights[1], LT_SPOT,
//			   -20.0f, 20.0f, 10.0f,	/* position */
//			   1.0f, -0.5f, 0.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 0.0f, 0.0f,	/* 照度(色) */
//			   30.f);						/* projection angle of spotlight */




//	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
//	init_shape(&scene->shapes[7], ST_PLANE,
//			   0.0, 0.0, 300.0,		/* 平面が通る点の位置 */
//			   0.0, 0.0, 1.0);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[7].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,								/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);
//
//
//	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
//	init_shape(&scene->shapes[8], ST_PLANE,
//			   0.0, 0.0, 300.0,		/* 平面が通る点の位置 */
//			   1.0, 0.0, 1.0);		/* 平面の法線ベクトル */
//
//	init_material(&scene->shapes[8].material,
//				  0.01f, 0.01f, 0.01f,	/* 環境光係数(RGB)   */
//				  0.69f, 0.69f, 0.69f,		/* 拡散反射係数(RGB) */
//				  0.30f, 0.30f, 0.30f,		/* 鏡面反射率(RGB)   */
//				  8.0f,								/* 光沢度 */
//				  MT_DEFAULT,
//				  0.0f, 0.0f, 0.0f,
//				  0.0f);



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
//	SET_COLOR(scene->ambient_illuminance, 0.1, 0.1, 0.1);

//	scene->num_lights_capacity = 1;
//	scene->num_lights = scene->num_lights_capacity;
//	scene->lights = (t_light *)malloc(sizeof(t_light) * scene->num_lights_capacity);

	/* outside */
//	init_light(&scene->lights[0], LT_POINT,
//			   50.0f, 50.0f, -50.0f, /* position */
//			   0.0f, 0.0f, 0.0f,	/* direction(do not use LT_POINT) */
//			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */

//	init_light(&scene->lights[0], LT_POINT,
//			   50.0f, 50.0f, -50.0f, /* 点光源の位置 */
//			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */

//	init_light(&scene->lights[0], LT_POINT,
//			   50.0f, 50.0f, -50.0f, /* 点光源の位置 */
//			   1.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */


//	init_light(&scene->lights[1], LT_POINT,
//			   5.0f, 10.0f, -50.0f, /* 点光源の位置 */
//			   0.0f, 1.0f, 1.0f);   /* 点光源の照度(色) */


	/* 平行光源の場合 */
//	init_light(&scene->lights[0], LT_DIRECTIONAL,
//			   50.0f, 100.0f, -50.0f,  /*平行光源の方向ベクトル */
//			   1.0f, 1.0f, 1.0f);  /* 平行光源の照度(色)*/

//	scene->global_refraction_index = 1.0f;

}