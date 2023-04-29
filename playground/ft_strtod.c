/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 10:41:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static bool	is_under_long(const long num, int digit, bool negative)
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

static bool	is_under_uint64(const uint64_t num, int digit)
{
	long of_div = UINT64_MAX / 10;
	long of_mod = UINT64_MAX % 10;

	if (num > of_div)
		return (false);
	if (num == of_div && digit >= of_mod)
		return (false);
	return (true);
}

static bool	is_under_int32(const int32_t num, int digit, bool negative)
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

static bool	is_under_int16(const int32_t num, int digit, bool negative)
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

//static int get_num_part(const char *str, double *num, double *sign, size_t *idx)
//{
//	double	scale;
//	size_t 	i;
//
//	while (isspace(str[*idx]))
//		*idx += 1;
//	if (str[*idx] == '-')
//		*sign = -1.0;
//	i = 0;
//	if (str[*idx + i] == '-' || str[*idx + i] == '+')
//		i++;
//	if (!str[*idx + i] || !(isdigit(str[*idx + i]) || (str[*idx + i] == '.' && isdigit(str[*idx + i + 1]))))
//		return (FAILURE);
//	*idx += i;
//	while ('0' <= str[*idx] && str[*idx] <= '9')
//	{
//		*num = *num * 10 + str[*idx] - '0';
////		printf("num:%f\n", *num);
//		*idx += 1;
//	}
//	if (str[*idx] == '.')
//	{
//		*idx += 1;
//		scale = 0.1;
//		while ('0' <= str[*idx] && str[*idx] <= '9')
//		{
//			*num += (double)(str[*idx] - '0') * scale;
//			scale *= 0.1;
//			*idx += 1;
//		}
//	}
//	return (SUCCESS);
//}
//
//static int	get_exp_part(const char *str, double *num, size_t *idx)
//{
//	double 	exp;
//	double 	exp_sign;
//	size_t 	i;
//
//	exp = 0.0;
//	exp_sign = 1.0;
//	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
//		return (SUCCESS);
//	i = 1;
//	if (!str[*idx + i])
//		return (FAILURE);
//	if (str[*idx + 1] == '-')
//		exp_sign = -1.0;
//	if (str[*idx + i] == '-' || str[*idx + i] == '+')
//		i++;
//	if (!str[*idx + i] || !isdigit(str[*idx + i]))
//		return (FAILURE);
//	while ('0' <= str[*idx + i] && str[*idx + i] <= '9')
//	{
//		exp = exp * 10 + str[*idx + i] - '0';
//		i++;
//	}
//	*num *= pow(10, exp * exp_sign);
//	*idx += i;
//	return (SUCCESS);
//}
//
//double	ft_strtod(const char *str, char **err)
//{
//	double	num;
//	double 	num_sign;
//	size_t	idx;
//
//	idx = 0;
//	num = 0.0;
//	num_sign = 1.0;
//	if (!str)
//	{
//		*err = (char *)&str[idx];
//		return (num);
//	}
//	if (get_num_part(str, &num, &num_sign, &idx) == FAILURE)
//	{
//		*err = (char *)&str[idx];
//		return (num);
//	}
//	if (get_exp_part(str, &num, &idx) == FAILURE)
//	{
//		*err = (char *)&str[idx];
//		return (num_sign * num);
//	}
//	*err = (char *)&str[idx];
//	return (num_sign * num);
//}


// ##############################################################################

#define	PARSER_MINUS_ZERO	2
#define PARSER_PLUS_ZERO	3
#define PARSER_MINUS_INF	4
#define PARSER_PLUS_INF		5

// (-1)^sign * 1.mantissa * 2^exponent
// b2b2b0
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

// ##############################################################################

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


// ##############################################################################

void	parse_sign_part(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;

	s = str;
	while (isspace(*s))
		s++;
	if (*s == '-')
		flt->negative = true;
	if ((*s == '-' || *s == '+'))
	{
		if (isdigit(s[1]) || (s[1] == '.' && isdigit(s[2])))
			s++;

	}
	*endptr = (char *)s;
}

void	parse_integer_part(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;
	int 		digit;
	bool		overflow;

	overflow = false;
#ifdef PRINT
	printf("=== parse_integer_part %s ===\n", str);
#endif
	s = str;
	while (*s == '0')
		s++;
	while (isdigit(*s))
	{
		digit = *s - '0';
		flt->int_exits = true;
		if (overflow)
			flt->exponent++;
		else if (is_under_uint64(flt->mantissa, digit))
			flt->mantissa = flt->mantissa * 10 + digit;
		else
		{
			overflow = true;
			flt->exponent++;
		}
		s++;
	}
//	printf("mantissa:%llu\n", flt->mantissa);
	*endptr = (char *)s;
}

// 10.00000 -> 10e0, != 1000000e-5
// 10.1     -> 101e-1
void	parse_decimal_part(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;
	int 		digit;
	bool		overflow;
	int 		zeros;

#ifdef PRINT
	printf("=== parse_decimal_part %s ===\n", str);
#endif

	s = str;
	overflow = false;
	zeros = 0;
	if (*s != '.')
	{
		*endptr = (char *)str;
		return ;
	}
	s++;
	if (!flt->int_exits && !isdigit(*s))
	{
		*endptr = (char *)str;
		return ;
	}

	// 0.000123 or 123.45

	// 0.00123 -> 1.23e-2
	if (flt->mantissa == 0 && *s == '0')
	{
		while (*s == '0')
		{
			s++;
//			zeros++;
			flt->exponent--;
		}
	}
	if (flt->mantissa != 0 && *s == '0')
	{
		while (*s == '0')
		{
			s++;
			zeros++;
		}
		if (isdigit(*s))
		{
			flt->exponent -= zeros;
			while (zeros)
			{
				if (!overflow && is_under_uint64(flt->mantissa, 0))
					flt->mantissa = flt->mantissa * 10 + 0;
				else
				{
					overflow = true;
					flt->exponent++;
				}
				zeros--;
			}

			flt->mantissa = flt->mantissa * pow(10, zeros);
		}
	}
	while (isdigit(*s))
	{
		digit = *s - '0';
		if (!overflow && is_under_uint64(flt->mantissa, digit))
			flt->mantissa = flt->mantissa * 10 + digit;
		else
		{
			overflow = true;
			flt->exponent++;
		}
		flt->exponent--;
		s++;
	}
//	printf("mantissa:%llu\n", flt->mantissa);
	*endptr = (char *)s;
}

void	parse_exponent_part(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;
	int 		digit;
	int32_t		exp;
	bool		negative;
	bool		overflow = false;

#ifdef PRINT
	printf("=== parse_exponent_part %s ===\n", str);
#endif

	s = str;
	negative = false;
	exp = 0;
	if (tolower(*s) != 'e')
	{
		*endptr = (char *)s;
		return ;
	}
	s++;
	if (*s == '-')
		negative = true;
	if (*s == '-' || *s == '+')
		s++;
	// e+0000123 -> e+123
	if (!isdigit(*s))
	{
		*endptr = (char *)str;
		return ;
	}
	while (*s == '0')
		s++;
	while (isdigit(*s))
	{
		digit = *s - '0';
		if (!overflow && is_under_int16(exp, digit, negative))	//todo:OF
			exp = exp * 10 + digit;
		else
		{
			if (negative)
				exp = INT16_MIN;
			else
				exp = INT16_MAX;
			overflow = true;
			exp++;
		}
		s++;
	}
	printf("exp:%d\n", exp);
	*endptr = (char *)s;

	if (!overflow && negative)
		exp = -exp;
	printf("exp:%d, of:%s\n", exp, overflow ? "true" : "false");
	flt->exponent += exp;
}

int	get_parse_result(t_float_info flt)
{
	if (flt.mantissa == 0)
	{
		if (flt.negative)
			return (PARSER_MINUS_ZERO);
		return (PARSER_PLUS_ZERO);
	}
	if (flt.exponent > 309)
	{
		if (flt.negative)
			return (PARSER_MINUS_INF);
		return (PARSER_PLUS_INF);
	}
	if (flt.exponent < -340)
	{
		if (flt.negative)
			return (PARSER_MINUS_ZERO);
		return (PARSER_PLUS_ZERO);
	}
	return (SUCCESS);
}

int	parse_float_str(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;
	char		*end;
	int 		parse_result;

	s = str;
	parse_sign_part(s, flt, &end);
#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", flt->negative ? "-" : "+");
	printf("  exponent:%d\n", flt->exponent);
	printf("  mantissa:%llu\n\n", flt->mantissa);
#endif
	s = end;
	parse_integer_part(s, flt, &end);
#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", flt->negative ? "-" : "+");
	printf("  exponent:%d\n", flt->exponent);
	printf("  mantissa:%llu\n\n", flt->mantissa);
#endif
	s = end;
	parse_decimal_part(s, flt, &end);
#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", flt->negative ? "-" : "+");
	printf("  exponent:%d\n", flt->exponent);
	printf("  mantissa:%llu\n\n", flt->mantissa);
#endif
	s = end;
	parse_exponent_part(s, flt, &end);

#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", flt->negative ? "-" : "+");
	printf("  exponent:%d\n", flt->exponent);
	printf("  mantissa:%llu\n\n", flt->mantissa);
#endif
	*endptr = end;

	parse_result = get_parse_result(*flt);
	return (parse_result);
}

// b2b1b0
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
void	convert_float_bin_to_double(t_float_info *flt)
{
	t_bit96			m = set_bit96(flt->mantissa);
	int32_t			bin_exp = 92;
	uint64_t		bin = 0x0000000000000000ULL;
	uint32_t		mask28 = 0xF << 28;
	uint32_t		mask20 = 0xFFF << 20;
	t_hex_double	hd;
	int				bit;
	uint64_t		t;

	// m' * 10^bin_exp' -> m * 2^bin_exp
	while (flt->exponent > 0)
	{
		// 4回 << 相当？
		m = add_bit96(left_shift_n_times(m, 1), left_shift_n_times(m, 3));
		flt->exponent--;

		//上位4ビットは0を維持
		m = keep_upper4_is0(m, &bin_exp);
//		flt->exponent--;
	}
	while (flt->exponent < 0)
	{
		while ((m.b2 & (1 << 31)) == 0)
		{
			m = left_shift_bit96(m);
			bin_exp--;
		}
		m = dev_by_ten(m);
		flt->exponent++;
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
		if (flt->negative)
			hd.u = 0.0;
	}
	else if (bin_exp > 2046)
	{
		if (flt->negative)
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
		if (flt->negative)
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
		if (flt->negative)
			hd.u |= (1ULL << 63);
	}
	// return
	flt->fp_num = hd.d;
}



double	convert_str2flt(t_float_info flt, int parse_result)
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

//	ret = pow(-1.0, flt.negative) * flt.mantissa * pow(10.0, flt.exponent);

	convert_float_bin_to_double(&flt);
	ret = flt.fp_num;
	return (ret);
}

void	init_flt(t_float_info *flt)
{
	flt->fp_num = 0.0;
	memset(&flt->fp_num, 0, sizeof(double));
	flt->negative = false;
	flt->exponent = 0;
	flt->mantissa = 0;
	flt->int_exits = false;
}

double	ft_strtod(const char *str, char **endptr)
{
	t_float_info	flt;
	char			*end;
	int 			parse_result;

//	printf("\n\n");
//	printf(" ========= strtod[%s] ========= \n", str);

	init_flt(&flt);
	parse_result = parse_float_str(str, &flt, &end);
	flt.fp_num = convert_str2flt(flt, parse_result);

//	printf("%f\n", flt.fp_num);
	if (endptr)
		*endptr = end;
	return (flt.fp_num);
}





