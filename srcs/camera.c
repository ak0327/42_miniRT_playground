/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:20:47 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 19:03:01 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_camera *camera)
{
	float		fov_radians;

//	SET_VECTOR(camera.pos, 0.0f, 5.0f, -10.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.2f, 1.0f)

//	SET_VECTOR(camera.pos, 0.0f, 0.0f, 0.0f)
//	SET_VECTOR(camera.dir, 0.0f, 0.0f, 1.0f)

/* corn */
//	SET_VECTOR(camera.pos, 5.0f, 25.0f, -50.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.3f, 1.0f)

/* spot */
//	SET_VECTOR(camera.pos, 0.0f, 25.0f, -60.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.3f, 1.0f)

/* bump */
//	sphere
//	SET_VECTOR(camera.pos, 0.0f, 100.0f, -600.0f)
//	SET_VECTOR(camera.dir, 0.0f, 0.0f, 1.0f)

//	cylinder

//	SET_VECTOR(camera.pos, -5.0f, 200.0f, -600.0f)
//	SET_VECTOR(camera.dir, 0.0f, -0.2f, 1.0f)


//	SET_VECTOR(camera.pos, 0.0f, 0.0f, -300.0f)
//	SET_VECTOR(camera.dir, 0.0f, 0.0f, 1.0f)


//	SET_VECTOR(camera.pos, 1000.0f, 0.0f, -1000.0f)
//	SET_VECTOR(camera.dir, 0.0f, 0.0f, 1.0f)
//	SET_VECTOR(camera.pos, 1000.0f, 0.0f, 1000.0f)
//	SET_VECTOR(camera.dir, -1.0f, 0.0f, -1.0f)


	normalize(&camera->dir);

	fov_radians  = camera->fov_deg * (float)M_PI / 180.0f;
	camera->distance_camera_to_sc = (WINDOW_HEIGHT * ASPECT / 2.0f) / tanf(fov_radians / 2.0f);
	camera->vec_camera_to_sc_center = mult(camera->distance_camera_to_sc, &camera->dir);

	camera->translate_matrix_w2c = get_tr_matrix_world2obj_yup(
			normalize_vec_inv(&camera->dir));
	camera->translate_matrix_c2w = transpose_matrix(camera->translate_matrix_w2c);
}