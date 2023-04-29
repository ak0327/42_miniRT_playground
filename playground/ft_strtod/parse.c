/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:10:47 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 16:40:30 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

void	parse_digit(t_parse_info *p, int digit, bool *overflow)
{
	if (!*overflow && is_under_uint64(p->mantissa, digit))
		p->mantissa = p->mantissa * 10 + digit;
	else
	{
		*overflow = true;
		p->exponent++;
	}
}

static void	parse_sign_part(const char *str, t_parse_info *p, char **endptr)
{
	const char	*s;

	s = str;
	while (isspace(*s))
		s++;
	if (*s == '-')
		p->negative = true;
	if ((*s == '-' || *s == '+'))
	{
		if (isdigit(s[1]) || (s[1] == '.' && isdigit(s[2])))
			s++;
	}
	*endptr = (char *)s;
}

static void	parse_integer_part(const char *str, t_parse_info *p, char **endptr)
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
		p->int_digit++;
		parse_digit(p, digit, &overflow);
		s++;
	}
//	printf("mantissa:%llu\n", p->mantissa);
	*endptr = (char *)s;
}

// 10.00000 -> 10e0, != 1000000e-5
// 10.1     -> 101e-1
void	parse_decimal_part(const char *str, t_parse_info *p, char **endptr)
{
	const char	*s;
	int 		digit;
	bool		overflow;
	int 		zero_cnt;

#ifdef PRINT
	printf("=== parse_decimal_part %s ===\n", str);
#endif

	s = str;
	overflow = false;
	*endptr = (char *)str;

	if (*s != '.')
		return ;
	s++;
	if (p->int_digit == 0 && !isdigit(*s))
		return ;

	// 0.00123 -> 1.23e-2
	zero_cnt = 0;
	while (*s == '0')
	{
		s++;
		zero_cnt++;
	}
	if (!isdigit(*s))
	{
		*endptr = (char *)s;
		return ;
	}

	p->exponent -= zero_cnt;
	if (p->mantissa != 0)
	{
		while (zero_cnt)
		{
			parse_digit(p, 0, &overflow);
			zero_cnt--;
		}
		p->mantissa = p->mantissa * pow(10, zero_cnt);
	}

	while (isdigit(*s))
	{
		digit = *s - '0';
		parse_digit(p, digit, &overflow);
		p->exponent--;
		s++;
	}
//	printf("mantissa:%llu\n", p->mantissa);
	*endptr = (char *)s;
}

void	parse_exponent_part(const char *str, t_parse_info *p, char **endptr)
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
	p->exponent += exp;
}

int	get_parse_result(t_parse_info p)
{
	if (p.mantissa == 0)
	{
		if (p.negative)
			return (PARSER_MINUS_ZERO);
		return (PARSER_PLUS_ZERO);
	}
	if (p.exponent > 309)
	{
		if (p.negative)
			return (PARSER_MINUS_INF);
		return (PARSER_PLUS_INF);
	}
	if (p.exponent < -340)
	{
		if (p.negative)
			return (PARSER_MINUS_ZERO);
		return (PARSER_PLUS_ZERO);
	}
	return (SUCCESS);
}

int	parse_float_str(const char *str, t_parse_info *p, char **endptr)
{
	const char	*s;
	char		*end;
	int 		parse_result;

	s = str;
	parse_sign_part(s, p, &end);
#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", p->negative ? "-" : "+");
	printf("  exponent:%d\n", p->exponent);
	printf("  mantissa:%llu\n\n", p->mantissa);
#endif
	s = end;
	parse_integer_part(s, p, &end);
#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", p->negative ? "-" : "+");
	printf("  exponent:%d\n", p->exponent);
	printf("  mantissa:%llu\n\n", p->mantissa);
#endif
	s = end;
	parse_decimal_part(s, p, &end);
#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", p->negative ? "-" : "+");
	printf("  exponent:%d\n", p->exponent);
	printf("  mantissa:%llu\n\n", p->mantissa);
#endif
	s = end;
	parse_exponent_part(s, p, &end);

#ifdef PRINT
	printf("[parse_float_str]\n");
	printf("  sign    :%s\n", p->negative ? "-" : "+");
	printf("  exponent:%d\n", p->exponent);
	printf("  mantissa:%llu\n\n", p->mantissa);
#endif
	*endptr = end;

	parse_result = get_parse_result(*p);
	return (parse_result);
}