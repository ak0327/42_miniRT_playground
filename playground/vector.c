/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:22:03 by takira            #+#    #+#             */
/*   Updated: 2023/03/08 12:47:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minirt.h"

int	main(void)
{
	t_vector v1, v2, v3;
	t_vector ans;

	init_vector(&v1, 3, 4, 5);
	init_vector(&v2, 6, 7, 8);
	init_vector(&v3, 9, 10, 11);
	printf("1. v1:%s\n", vector_str(&v1));
	printf("2. v2:%s\n", vector_str(&v2));
	printf("3. v3:%s\n", vector_str(&v3));

	ans = add(&v1, &v2);
	printf("4. v1+v2:%s\n", vector_str(&ans));

	t_vector a1, b1;
	a1 = mult(3, &v1);
	b1 = mult(4, &v2);
	ans = add(&a1, &b1);
	printf("5. 3v1 + 4v2:%s\n", vector_str(&ans));

	a1 = mult(2, &v1);
	b1 = mult(5, &v2);
	t_vector c1, d1;
	c1 = mult(10, &v3);
	d1 = sub(&a1, &b1);
	ans = add(&d1, &c1);
	printf("6. 2v1 - 5v2 + 10v3:%s\n", vector_str(&ans));

	printf("7. v2*v3:%f\n", dot(&v2, &v3));

	cross(&ans, &v2, &v3);
	printf("8. v2xv3:%s\n", vector_str(&ans));
}