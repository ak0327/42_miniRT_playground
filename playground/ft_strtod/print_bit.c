/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:59:45 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 19:00:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

void	print_bit_int32(int32_t b)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		printf("%d", (b >> i) & 1);
		i--;
	}
}

void	print_bit_uint64(uint64_t b)
{
	int i;

	i = 63;
	for (int j=0; j<33; j++)
		printf(" ");

	while (i >= 0)
	{
		printf("%lld", (b >> i) & 1);
		if (i == 32)
			printf(" ");
		i--;
	}
	printf("\n");
}

void	print_bit_uint128(t_uint128 b)
{
	print_bit_uint64(b.b1);
	printf(" ");
	print_bit_uint64(b.b0);
	printf("\n");
}
