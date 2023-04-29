/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:00 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 16:47:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

typedef struct	s_bit96
{
	uint32_t	b2;
	uint32_t	b1;
	uint32_t	b0;
}	t_bit96;

typedef struct	s_float_info
{
	double		fp_num;
	bool		negative;
	int32_t		exponent;
	uint64_t	mantissa;
	bool		int_exits;
}			t_float_info;

t_bit96	add_bit96(t_bit96 a, t_bit96 b)
{
	uint64_t	c;
	t_bit96		add;

	c = (uint64_t)a.b0 + (uint64_t)b.b0;
	add.b0 = c;
	c >>= 32;
	c += (uint64_t)a.b1 + (uint64_t)b.b1;
	add.b1 = c;
	c >>= 32;
	c += (uint64_t)a.b2 + (uint64_t)b.b2;
	add.b2 = c;
	return (add);
}

t_bit96	sub_bit96(t_bit96 a, t_bit96 b)
{
	uint64_t	c;
	t_bit96		add;

	c = (uint64_t)a.b0 - (uint64_t)b.b0;
	add.b0 = c;
	c >>= 32;
	c += (uint64_t)a.b1 - (uint64_t)b.b1;
	add.b1 = c;
	c >>= 32;
	c += (uint64_t)a.b2 - (uint64_t)b.b2;
	add.b2 = c;
	return (add);
}

t_bit96	right_shift_bit96(t_bit96 a)
{
	t_bit96	shift;

	shift.b0 = (a.b0 >> 1) | ((a.b1 & 1) << 31);
	shift.b1 = (a.b1 >> 1) | ((a.b2 & 1) << 31);
	shift.b2 = (a.b2 >> 1);
	return (shift);
}

t_bit96	left_shift_bit96(t_bit96 a)
{
	t_bit96	shift;

	shift.b0 = (a.b0 << 1);
	shift.b1 = (a.b1 << 1) | ((a.b0 & 0x80000000) >> 31);
	shift.b2 = (a.b2 << 1) | ((a.b1 & 0x80000000) >> 31);
	return (shift);
}

t_bit96 right_shift_n_times(t_bit96 b, int n)
{
	while (n > 0)
	{
		b = right_shift_bit96(b);
		n--;
	}
	return (b);
}

t_bit96 left_shift_n_times(t_bit96 b, int n)
{
	while (n > 0)
	{
		b = left_shift_bit96(b);
		n--;
	}
	return (b);
}

t_bit96	set_bit96(int64_t mantissa)
{
	t_bit96	f;

	f.b2 = 0;
	f.b1 = (uint32_t)(mantissa >> 32);
	f.b0 = (uint32_t)(mantissa & 0xffffffff);
	return (f);
}

void	print_bit32(int32_t b)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		printf("%d", (b >> i) & 1);
		i--;
	}
}

void	print_bit64(int64_t b)
{
	int64_t i;

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

void	print_bit96(t_bit96 f)
{
	print_bit32(f.b2);
	printf(" ");
	print_bit32(f.b1);
	printf(" ");
	print_bit32(f.b0);
	printf("\n");
}

// todo: ここむずい
t_bit96	dev_by_ten(t_bit96 b)
{
	t_bit96 q, r, s;

	s = b;
	q.b2 = s.b2 / 10;
	r.b1 = s.b2 % 10;
	r.b2 = (r.b1 << 24) | (s.b1 >> 8);
	q.b1 = r.b2 / 10;
	r.b1 = r.b2 % 10;
	r.b2 = (r.b1 << 24) | ((s.b1 & 0xFF) << 16) | (s.b0 >> 16);
	r.b0 = r.b2 / 10;
	r.b1 = r.b2 % 10;
	q.b0 = ((r.b1 << 16)| (s.b0 & 0xFFFF)) / 10 | (r.b0 << 16);
	q.b1 = ((r.b0 & 0x00FF0000) >> 16) | (q.b1 << 8);
	s.b2 = q.b2;
	s.b1 = q.b1;
	s.b0 = q.b0;
	return (s);
}

t_bit96 keep_upper4_is0(t_bit96 m, int *e)
{
	uint32_t		mask28 = 0xF << 28;

	while (m.b2 & mask28)
	{
		m = right_shift_bit96(m);
		*e += 1;
	}

//	int i = 0;

//	while (i < 4)
//	{
//		if (m.b2 & (1 << (32 - i)))
//		{
//			m = right_shift_n_times(m, 4 - i);
//			*e += 4 - 1;
//			break ;
//		}
//		i++;
//	}
	return (m);
}

t_bit96	round_ties_even(t_bit96 s, int bit)
{
	uint32_t	even;
	uint32_t	mask;
	uint32_t	min_bit;
	t_bit96		add;

	if (bit > 4 && bit <= 32)
	{
		even = 1 << (32 - bit);
		min_bit = even << 1;
		mask = min_bit - 1;
		add.b0 = 0;
		add.b1 = 0;
		add.b2 = min_bit;
		if (((s.b2 & mask) == even) && !s.b1 && !s.b0)
		{
			if (s.b2 & min_bit)
			{
				s.b2 &= ~mask;
				s = add_bit96(s, add);
			}
			else
			{
				s.b2 &= ~mask;
				s.b1 = 0;
				s.b0 = 0;
			}
		}
		else if (s.b2 & even)
		{
			s.b2 &= ~mask;
			s = add_bit96(s, add);
		}
		else
		{
			s.b2 &= ~mask;
			s.b1 = 0;
			s.b0 = 0;
		}
	}
	else
	{
		// 該当するビット
		even = 1 << (32 - (bit - 32));
		min_bit = even << 1;
		mask = min_bit - 1;
		add.b0 = 0;
		add.b1 = min_bit;
		add.b2 = 0;
		if (((s.b1 & mask) == even)  && !s.b0)
		{
			if (s.b1 & min_bit)
			{
				s.b1 &= ~mask;
				s = add_bit96(s, add);
			}
			else
			{
				s.b1 &= ~mask;
				s.b0 = 0;
			}
		}
		else if (s.b1 & even) // 大きいとき
		{
			s.b1 &= ~mask;
			s = add_bit96(s, add);
		}
		else
		{
			s.b1 &= ~mask;
			s.b0 = 0;
		}
	}
	return (s);
}

typedef union	u_hex_double {
	double		d;
	uint64_t	u;
}				t_hex_double;

double convert_float_bin_to_double(t_parse_info *p)
{
	t_bit96			m = set_bit96(p->mantissa);
	int32_t			bin_exp = 92;
	uint32_t		mask28 = 0xF << 28;
	uint32_t		mask20 = 0xFFF << 20;
	t_hex_double	hd;
	int				bit;
	uint64_t		t;

	// m' * 10^bin_exp' -> m * 2^bin_exp
	while (p->exponent > 0)
	{
		// 4回 << 相当？
		m = add_bit96(left_shift_n_times(m, 1), left_shift_n_times(m, 3));
		p->exponent--;

		//上位4ビットは0を維持
		m = keep_upper4_is0(m, &bin_exp);
//		p->exponent--;
	}
	while (p->exponent < 0)
	{
		while ((m.b2 & (1 << 31)) == 0)
		{
			m = left_shift_bit96(m);
			bin_exp--;
		}
		m = dev_by_ten(m);
		p->exponent++;
	}
	// bitshift for m
	// ここはeをいじっていいのか？
	if (m.b2 || m.b1 || m.b0)
	{
		while ((m.b2 & mask28) == 0)
		{
			m = left_shift_bit96(m);
			bin_exp--;
		}
	}

	bin_exp += 1023;

	hd.u = 0x0000000000000000ULL;

	// validate ?
	if (bin_exp < -52)
	{
		if (p->negative)
			hd.u = 0.0;
	}
	else if (bin_exp > 2046)
	{
		if (p->negative)
			hd.u = -INFINITY;
		else
			hd.u = INFINITY;
	}
	else if (bin_exp >= -52 && bin_exp < 1)
	{
		bit = bin_exp + 56;
		m = round_ties_even(m, bit);
		m = left_shift_n_times(m, 62 - bit + 1);
		hd.u = (uint64_t)m.b1 | ((uint64_t)(m.b2 & ~mask20) << 32);
		if (p->negative)
			hd.u |= (1ULL << 63);
	}
	else if (m.b2)
	{
		uint64_t binexs2 = (uint64_t)bin_exp;
		// 完全に等しい時
		bit = 7;
		if (m.b1 & (1 << bit) && (!(m.b1 & ((1 << bit) - 1)) && !(m.b0)))
		{
			if ((m.b1 >> (bit + 1)) & 1)
				t = (m.b1 >> (bit + 1)) + 1; // 偶数方向に1足す
			else
				t = (m.b1 >> (bit + 1)); // すでに最下位ビットが0
		}
		else if (!(m.b1 & (1 << bit))) // 0x10000000のビットが立ってない時は切り捨てればよい
			t = (m.b1 >> (bit + 1));
			// 下位40ビットが0x10000000 00000000000000000000000000000000より大きい場合s1のビットを一つ大きくする
		else
			t = (m.b1 >> (bit + 1)) + 1;
		hd.u = (binexs2 << 52) | ((uint64_t)(m.b2 & ~mask28) << 24) | t;
		if (p->negative)
			hd.u |= (1ULL << 63);
	}
	// return
	return (hd.d);
}

double	convert_to_double(t_parse_info p, int parse_result)
{
	double	ret;

	if (parse_result == PARSER_MINUS_ZERO)
		return (-0.0);
	if (parse_result == PARSER_PLUS_ZERO)
		return (+0.0);
	if (parse_result == PARSER_MINUS_INF)
		return (-INFINITY);
	if (parse_result == PARSER_PLUS_INF)
		return (INFINITY);

	ret = convert_float_bin_to_double(&p);
	return (ret);
}