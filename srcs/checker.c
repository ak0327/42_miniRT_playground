/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:19:43 by takira            #+#    #+#             */
/*   Updated: 2023/03/21 17:01:33 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	get_checker_color(const t_scene *scene, const t_ray *eye_ray,
							  t_intersection_point intp, t_shape *shape)
{
	t_vector	u, v;
	t_vector	n = intp.normal;
	float		unit;

	u.x = n.z / sqrtf(SQR(n.x) + SQR(n.z));
	u.y = 0;
	u.z = -1 * n.x / sqrtf(SQR(n.x) + SQR(n.z));
	normalize(&u);

	v = cross(&n, &u);
	normalize(&v);

	if (n.x == 0 && n.y != 0 && n.z == 0)
	{
		unit = 1.0f;
		if (n.y > 0)
			unit = -1.0f;
		SET_VECTOR(u, unit, 0.0f, 0.0f);
		SET_VECTOR(v, 0.0f, 0.0f, unit);
	}

	// ここからどうする...??

}