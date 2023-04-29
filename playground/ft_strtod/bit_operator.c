/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:26:02 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 18:50:08 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

void	memset_uint128(t_uint128 *bit, unsigned char set)
{
	memset(&(bit->b1), set, sizeof(uint64_t));
	memset(&(bit->b0), set, sizeof(uint64_t));
}

t_uint128	set_bit(int64_t b1, int64_t b0)
{
	t_uint128	bit;

	bit.b1 = b1;
	bit.b0 = b0;
	return (bit);
}

t_uint128	right_n_shift_u128(t_uint128 bit, unsigned int n)
{
	t_uint128		result;

	if (n >= 64)
	{
		result.b0 |= bit.b1 >> (64 - n);
		result.b0 = 0ULL;
	}
	else
	{
		result.b1 = bit.b1 >> n;
		result.b0 = bit.b1 << (64 - n) | bit.b0 >> n;
	}
	return (result);
}

t_uint128	left_n_shift_u128(t_uint128 bit, unsigned int n)
{
	t_uint128	result;

	if (n >= 64)
	{
		result.b0 = 0ULL;
		result.b1 = bit.b0 << (n - 64);
	}
	else
	{
		result.b0 = bit.b0 << (64 - n);
		result.b1 = bit.b1 << n | bit.b0 >> (64 - n);
	}
	return (result);
}

t_uint128	add_u128(t_uint128 a, t_uint128 b)
{
	t_uint128	result;

	result.b0 = a.b0 + b.b0;
	result.b1 = a.b1 + b.b1;
	return (result);
}

t_uint128	multiply_by_ten(t_uint128 bit)
{
	t_uint128	result;

	result = add_u128(left_n_shift_u128(bit, 1), left_n_shift_u128(bit, 3));
	return (result);
}

// todo: わからん
t_uint128	divide_by_ten(t_uint128 bit)
{
	t_uint128	result;
	uint64_t 	tmp1, tmp2, tmp3;

	result.b0 = bit.b0 / 10;
	tmp1 = ((bit.b0 % 10) << 32) | (bit.b1 >> 32);
	tmp2 = tmp1 / 10;
	tmp3 = ((tmp1 % 10) << 32) | (bit.b1 & 0xFFFFFFFF) / 10;
	result.b1 = (tmp2 << 32) | tmp3;
	return (result);
}
