/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:00 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 21:24:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

// m * 10^e -> m' * 2^e'
static t_uint128	trans_exp_dec2bin(t_fmt *f, int32_t dec_exp)
{
	t_uint128	bin;

	bin = set_bit(0ULL, f->mantissa);

	while (dec_exp > 0)
	{
		multiply_by_ten(bin);
		dec_exp--;
		while (bin.b1 & MASK60)
		{
			bin = right_n_shift_u128(bin, 1);
			f->exponent++;
		}
	}
	while (dec_exp < 0)
	{
		while ((bin.b1 & (1ULL << 63)) == 0)
		{
			bin = left_n_shift_u128(bin, 1);
			f->exponent--;
		}
		bin = divide_by_ten(bin);
		dec_exp++;
	}
	f->exponent += 1023;
	return (bin);
}

static t_uint128	shift_mantissa(t_fmt *f, t_uint128 bin)
{
	if (!bin.b1 && !bin.b0)
		return (bin);

	while (bin.b1 & MASK60)
	{
		bin = right_n_shift_u128(bin, 1);
		f->exponent++;
	}
	while ((bin.b1 & MASK60) == 0)
	{
		bin = left_n_shift_u128(bin, 1);
		f->exponent--;
	}
	return (bin);
}

static int validate_fmt(t_fmt *f)
{
	if (f->exponent < -52)
	{
		if (f->negative)
			return (MINUS_ZERO);
		return (PLUS_ZERO);
	}
	if (f->exponent > 2046)
	{
		if (f->negative)
			return (MINUS_INF);
		return (PLUS_INF);
	}
	return (SUCCESS);
}

static double	ret_num(int res)
{
	if (res == MINUS_ZERO)
		return (-0.0);
	if (res == PLUS_ZERO)
		return (0.0);
	if (res == MINUS_INF)
		return (-INFINITY);
	return (INFINITY);
}

static t_uint128	round_ties_even(t_uint128 bin, int bit)
{

}

static void	rounding(t_fmt *f, t_uint128 bin)
{
	int	b;

	if (-52 <= f->exponent && f->exponent < 1)
	{
		b = f->exponent + 56;
		bin = round_ties_even(bin, b);
		bin = left_n_shift_u128(bin, 62 - b + 1);
		f->mantissa = (uint64_t)bin.b0;
	}
	else if (bin.b1)
	{

	}
}

static t_mem2num	convert_bin2num(t_fmt *f)
{
	t_mem2num	m;

	m.mem = 0;
	m.num = 0.0;

	if (f->negative)
		m.mem = (1ULL << 63);
	m.mem |= ((uint64_t)f->exponent << 52);
	m.mem |= ((uint64_t)f->mantissa);
	return (m);
}

static void	init_fmt(t_parse_info *p, t_fmt *f)
{
	f->negative = p->negative;
	f->exponent = 0;
	f->mantissa = f->mantissa;
}

static double	convert_dec2bin2num(t_parse_info *p, t_fmt *f)
{
	t_mem2num	m;
	t_uint128	bin;
	int 		validate_result;

	bin = trans_exp_dec2bin(f, p->exponent);
	bin = shift_mantissa(f, bin);

	validate_result = validate_fmt(f);
	if (validate_result != SUCCESS)
		return (ret_num(validate_result));

	// rounding
	rounding(f, bin);

	// bin2num
	m = convert_bin2num(f);
	return (m.num);
}

double	convert_to_double_(t_parse_info *p, int parse_result)
{
	t_fmt	fmt;
	double	ret;

	if (parse_result == MINUS_ZERO)
		return (-0.0);
	if (parse_result == PLUS_ZERO)
		return (+0.0);
	if (parse_result == MINUS_INF)
		return (-INFINITY);
	if (parse_result == PLUS_INF)
		return (INFINITY);

	ret = convert_dec2bin2num(p, &fmt);
	return (ret);
}