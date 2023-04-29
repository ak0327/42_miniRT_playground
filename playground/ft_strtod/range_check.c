/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:17:45 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 16:20:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

bool	is_under_long(const long num, int digit, bool negative)
{
	long of_div = LONG_MAX / 10;
	long of_mod = LONG_MAX % 10;
	if (negative)
	{
		of_div = -(LONG_MIN / 10);
		of_mod = -(LONG_MIN % 10);
	}

	if (num > of_div)
		return (false);
	if (num == of_div && digit >= of_mod)
		return (false);
	return (true);
}

bool	is_under_uint64(const uint64_t num, int digit)
{
	long of_div = UINT64_MAX / 10;
	long of_mod = UINT64_MAX % 10;

	if (num > of_div)
		return (false);
	if (num == of_div && digit >= of_mod)
		return (false);
	return (true);
}

bool	is_under_int32(const int32_t num, int digit, bool negative)
{
	long of_div = INT32_MAX / 10;
	long of_mod = INT32_MAX % 10;
	if (negative)
	{
		of_div = -(INT32_MIN / 10);
		of_mod = -(INT32_MIN % 10);
	}

	if (num > of_div)
		return (false);
	if (num == of_div && digit >= of_mod)
		return (false);
	return (true);
}

bool	is_under_int16(const int32_t num, int digit, bool negative)
{
	long of_div = INT16_MAX / 10;
	long of_mod = INT16_MAX % 10;
	if (negative)
	{
		of_div = -(INT16_MIN / 10);
		of_mod = -(INT16_MIN % 10);
	}

	if (num > of_div)
		return (false);
	if (num == of_div && digit >= of_mod)
		return (false);
	return (true);
}
