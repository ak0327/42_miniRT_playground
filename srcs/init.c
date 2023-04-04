/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:46:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/04 19:24:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void init_light(t_light *light, t_light_type lt,
				float px, float py, float pz,
				float dirx, float diry, float dirz,
				float illR, float illG, float illB)
{
	light->type = lt;
	SET_VECTOR(light->position, px, py, pz);
	SET_VECTOR(light->direction, dirx, diry, dirz);
	SET_COLOR(light->illuminance, illR, illG, illB);
}

void init_shape(t_shape *shape, t_shape_type st, ...)
{
	va_list args;
	va_start(args, st);

	shape->type = st;
	if (st == ST_SPHERE)
	{
		t_sphere *sph = &shape->data.sphere;

		sph->center.x = va_arg(args, double);
		sph->center.y = va_arg(args, double);
		sph->center.z = va_arg(args, double);
		sph->radius   = va_arg(args, double);
	}
	else if (st == ST_PLANE)
	{
		t_plane *plane = &shape->data.plane;

		plane->position.x = va_arg(args, double);
		plane->position.y = va_arg(args, double);
		plane->position.z = va_arg(args, double);

		plane->normal.x = va_arg(args, double);
		plane->normal.y = va_arg(args, double);
		plane->normal.z = va_arg(args, double);
		normalize(&plane->normal);
	}
	else if (st == ST_CYLINDER)
	{
		t_cylinder *cylinder = &shape->data.cylinder;

		cylinder->normal.x = va_arg(args, double);
		cylinder->normal.y = va_arg(args, double);
		cylinder->normal.z = va_arg(args, double);
		normalize(&cylinder->normal);

		cylinder->position.x = va_arg(args, double);
		cylinder->position.y = va_arg(args, double);
		cylinder->position.z = va_arg(args, double);

		cylinder->height = va_arg(args, double);
		cylinder->radius = va_arg(args, double);
	}
	else if (st == ST_CORN)
	{
		t_corn *corn = &shape->data.corn;

		corn->normal.x = va_arg(args, double);
		corn->normal.y = va_arg(args, double);
		corn->normal.z = va_arg(args, double);
		normalize(&corn->normal);

		corn->position.x = va_arg(args, double);
		corn->position.y = va_arg(args, double);
		corn->position.z = va_arg(args, double);

		corn->height = va_arg(args, double);
		corn->radius = va_arg(args, double);
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
				   float refR, float refG, float refB,
				   float refraction_index)
{
	SET_COLOR(mat->ambient_ref,  ambR, ambG, ambB);
	SET_COLOR(mat->diffuse_ref,  difR, difG, difB);
//	SET_COLOR(mat->diffuse_ref_checker,  difR_c, difG_c, difB_c);
	SET_COLOR(mat->specular_ref, speR, speG, speB);
	mat->shininess = shns;
	mat->type = type;
	SET_COLOR(mat->reflect_ref, refR, refG, refB);
	mat->refraction_index = refraction_index;
}
