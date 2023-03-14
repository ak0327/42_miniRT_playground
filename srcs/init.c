/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:46:48 by takira            #+#    #+#             */
/*   Updated: 2023/03/14 09:58:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void init_light(t_light *light, t_light_type lt,
				float vx, float vy, float vz,
				float illR, float illG, float illB)
{
	light->type = lt;
	SET_VECTOR(light->vector, vx, vy, vz);
	SET_COLOR(light->illuminance, illR, illG, illB);
}

void init_shape(t_shape *shape, t_shape_type st, ...)
{
	va_list args;
	va_start(args, st);

	shape->type = st;
	if ( st == ST_SPHERE )
	{
		t_sphere *sph = &shape->data.sphere;

		sph->center.x = va_arg(args, double);
		sph->center.y = va_arg(args, double);
		sph->center.z = va_arg(args, double);
		sph->radius   = va_arg(args, double);
	}
	else if ( st == ST_PLANE )
	{
		t_plane *plane = &shape->data.plane;

		plane->position.x = va_arg(args, double);
		plane->position.y = va_arg(args, double);
		plane->position.z = va_arg(args, double);

		plane->normal.x = va_arg(args, double);
		plane->normal.y = va_arg(args, double);
		plane->normal.z = va_arg(args, double);
	}
	else
	{
		fprintf(stderr, "init_shape : unknown shape type.\n");
		abort();
	}

	va_end(args);
}

void init_material(t_material *mat,
				   float ambR, float ambG, float ambB,
				   float difR, float difG, float difB,
				   float speR, float speG, float speB,
				   float shns,
				   t_material_type type,
				   float refR, float refG, float refB)
{
	SET_COLOR(mat->ambient_ref,  ambR, ambG, ambB);
	SET_COLOR(mat->diffuse_ref,  difR, difG, difB);
	SET_COLOR(mat->specular_ref, speR, speG, speB);
	mat->shininess = shns;
	mat->type = type;
	SET_COLOR(mat->reflect_ref, refR, refG, refB);
}
