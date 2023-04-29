/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:28 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 18:00:01 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOD_H
#define FT_STRTOD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <sys/errno.h>
#include <float.h>

#define SUCCESS	0
#define FAILURE	1

#define	PARSER_MINUS_ZERO	2
#define PARSER_PLUS_ZERO	3
#define PARSER_MINUS_INF	4
#define PARSER_PLUS_INF		5

#define MASK20	(0xFFF << 20)
#define MASK28	(0xF << 28)


typedef struct s_parse_info
{
	bool		negative;
	int32_t		exponent;
	uint64_t	mantissa;
	int			int_digit;
}				t_parse_info;

typedef struct s_parse_exponent
{
	bool		negative;
	int32_t		exponent;
	bool		overflow;
}				t_parse_exponent;

// b1 b0
typedef	struct s_uint128
{
	uint64_t	b1;
	uint64_t	b0;
}			t_uint128;

typedef union u_tr_bit2double
{
	uint64_t	b;
	double 		d;
}			t_b2d;


int			parse_float_str(const char *str, t_parse_info *flt, char **endptr);
double		convert_to_double(t_parse_info p, int parse_res);
double		ft_strtod(const char *str, char **err);

bool		is_under_int16(const int32_t num, int digit, bool negative);
bool		is_under_int32(const int32_t num, int digit, bool negative);
bool		is_under_uint64(const uint64_t num, int digit);
bool		is_under_long(const long num, int digit, bool negative);

t_uint128	set_bit(int64_t b1, int64_t b0);






#endif //FT_STRTOD_H
