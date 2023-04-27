/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 19:18:37 by takira           ###   ########.fr       */
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

// (-1)^sign * 1.mantissa * 2^exponent
typedef struct	s_bit96
{
	uint32_t	b2;
	uint32_t	b1;
	uint32_t	b0;
}	t_bit96;

typedef struct	s_float_info
{
	double		fp_num;
	int8_t		sign;
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


// ##############################################################################

void	parse_sign_part(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;

	s = str;
	while (isspace(*s))
		s++;
	if (*s == '-')
		flt->sign = 1;
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
//	printf("=== parse_integer_part %s ===\n", str);
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

void	parse_decimal_part(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;
	int 		digit;
	bool		overflow;

//	printf("=== parse_decimal_part %s ===\n", str);
	s = str;
	overflow = false;
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
			flt->exponent--;
		}
	}
	while (isdigit(*s))
	{
		digit = *s - '0';
		if (overflow)
			flt->exponent++;
		if (is_under_uint64(flt->mantissa, digit))
			flt->mantissa = flt->mantissa * 10 + digit;
		else if (!overflow)
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

//	printf("=== parse_exponent_part %s ===\n", str);
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
		if (is_under_int32(exp, digit, negative))	//todo:OF
			exp = exp * 10 + digit;
		else
		{
			if (negative)
				exp = INT32_MIN;
			else
				exp = INT32_MAX;
			exp++;
		}
		s++;
	}
//	printf("exp:%d\n", exp);
	if (negative)
		exp = -exp;
	flt->exponent += exp;
	*endptr = (char *)s;
}

void	str_to_floatbin(const char *str, t_float_info *flt, char **endptr)
{
	const char	*s;
	char		*end;

	s = str;
	parse_sign_part(s, flt, &end);
//	printf("[str_to_floatbin]\n");
//	printf("  sign    :%d\n", flt->sign);
//	printf("  exponent:%d\n", flt->exponent);
//	printf("  mantissa:%llu\n\n", flt->mantissa);
	s = end;
	parse_integer_part(s, flt, &end);
//	printf("[str_to_floatbin]\n");
//	printf("  sign    :%d\n", flt->sign);
//	printf("  exponent:%d\n", flt->exponent);
//	printf("  mantissa:%llu\n\n", flt->mantissa);
	s = end;
	parse_decimal_part(s, flt, &end);
//	printf("[str_to_floatbin]\n");
//	printf("  sign    :%d\n", flt->sign);
//	printf("  exponent:%d\n", flt->exponent);
//	printf("  mantissa:%llu\n\n", flt->mantissa);
	s = end;
	parse_exponent_part(s, flt, &end);
//	printf("[str_to_floatbin]\n");
//	printf("  sign    :%d\n", flt->sign);
//	printf("  exponent:%d\n", flt->exponent);
//	printf("  mantissa:%llu\n\n", flt->mantissa);
	*endptr = end;
}

void	float_bin_to_double(t_float_info *flt)
{

}

void	init_flt(t_float_info *flt)
{
	flt->fp_num = 0.0;
	memset(&flt->fp_num, 0, sizeof(double));
	flt->sign = 0;
	flt->exponent = 0;
	flt->mantissa = 0;
	flt->int_exits = false;

}

double	ft_strtod(const char *str, char **endptr)
{
	t_float_info	flt;
	char			*end;

//	printf("\n\n");
//	printf(" ========= strtod[%s] ========= \n", str);
	init_flt(&flt);
	str_to_floatbin(str, &flt, &end);
	float_bin_to_double(&flt);
	flt.fp_num = pow(-1.0, flt.sign) * flt.mantissa * pow(10.0, flt.exponent);
//	printf("%f\n", flt.fp_num);
	if (endptr)
		*endptr = end;
	return (flt.fp_num);
}


//int main(void)
//{
//
//	ft_strtod("123.456", NULL);
//
//	return (0);
//}



















