/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 17:40:01 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ref: https://note.com/sukesan1984/n/ncd78a5d6251c

void	print_float_bit(double double_num, char *str);

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <libc.h>
#include <sys/errno.h>
#include <limits.h>
#include <math.h>

#define DOUBLE_PLUS_ZERO		0x0000000000000000ULL
#define DOUBLE_MINUS_ZERO		0x8000000000000000ULL
#define DOUBLE_PLUS_INFINITY	0x7FF0000000000000ULL
#define DOUBLE_MINUS_INFINITY	0xFFF0000000000000ULL

#define FSM_WS 0
#define FSM_SON 1
#define FSM_LZOM 2
#define FSM_LZOF 3
#define FSM_MIP 4
#define FSM_MFP 5
#define FSM_ES 6
#define FSM_ELZ 7
#define FSM_E 8
#define FSM_STOP 9

#define PARSER_OK 0
#define PARSER_PZERO 1
#define PARSER_MZERO 2
#define PARSER_PINF 3
#define PARSER_MINF 4

#define DIGITS 18

# include <stdint.h>

typedef struct	s_bit96 {
	uint32_t	s2;
	uint32_t	s1;
	uint32_t	s0;
}				t_bit96;

typedef struct	s_prep_number {
	int			negative;
	int32_t		exponent;
	uint64_t	mantissa;
}				t_prep_number;

typedef union	u_hex_double {
	double		d;
	uint64_t	u;
}				t_hex_double;
t_bit96	add96(t_bit96 s, t_bit96 d)
{
	uint64_t	w;
	t_bit96		new;

	w = (uint64_t)s.s0 + (uint64_t)d.s0;
	new.s0 = w;
	w >>= 32;
	w += (uint64_t)s.s1 + (uint64_t)d.s1;
	new.s1 = w;
	w >>= 32;
	w += (uint64_t)s.s2 + (uint64_t)d.s2;
	new.s2 = w;
	return (new);
}

t_bit96	sub96(t_bit96 s, t_bit96 d)
{
	uint64_t	w;
	t_bit96		new;

	w = (uint64_t)s.s0 - (uint64_t)d.s0;
	new.s0 = w;
	w >>= 32;
	w += (uint64_t)s.s1 - (uint64_t)d.s1;
	new.s1 = w;
	w >>= 32;
	w += (uint64_t)s.s2 - (uint64_t)d.s2;
	new.s2 = w;
	return (new);
}

t_bit96	lsr96(t_bit96 s)
{
	t_bit96	new;

	new.s0 = (s.s0 >> 1) | ((s.s1 & 1) << 31);
	new.s1 = (s.s1 >> 1) | ((s.s2 & 1) << 31);
	new.s2 = (s.s2 >> 1);
	return (new);
}

t_bit96	lsr96_bit(t_bit96 s, int i)
{
	while (i > 0)
	{
		s = lsr96(s);
		i--;
	}
	return (s);
}

t_bit96	lsl96(t_bit96 s)
{
	t_bit96	new;

	new.s0 = (s.s0 << 1);
	new.s1 = (s.s1 << 1) | ((s.s0 & 0x80000000) >> 31);
	new.s2 = (s.s2 << 1) | ((s.s1 & 0x80000000) >> 31);
	return (new);
}

// bitの位置で偶数丸めする
// 先頭から何ビット目以降を丸めるか?(bit)
// s2: 0x1 0000000 (28ビット)
// s1: 0x000000 00 (24 + 8ビット)
// s0: 0x00000000 (32ビット)
// 例えば、52ビットフルに使う場合丸めるの
// 53ビット目 (s1の25ビット目以降) (bit = 53 + 8)
// s1の下位8ビットが0x80より小さいか等しいか大きいかで分岐する
// 0x80と等しい場合
// もし、s1の24ビット目が1なら0x100を足す0なら下位8ビットを切り捨てる
// 0x80より小さい場合
// 切り捨て
// 0x80より大きい場合
// 0x100を足す
// bit: 5bit - 57 bit
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
		add.s0 = 0;
		add.s1 = 0;
		add.s2 = min_bit;
		if (((s.s2 & mask) == even) && !s.s1 && !s.s0)
		{
			if (s.s2 & min_bit)
			{
				s.s2 &= ~mask;
				s = add96(s, add);
			}
			else
			{
				s.s2 &= ~mask;
				s.s1 = 0;
				s.s0 = 0;
			}
		}
		else if (s.s2 & even)
		{
			s.s2 &= ~mask;
			s = add96(s, add);
		}
		else
		{
			s.s2 &= ~mask;
			s.s1 = 0;
			s.s0 = 0;
		}
	}
	else
	{
		// 該当するビット
		even = 1 << (32 - (bit - 32));
		min_bit = even << 1;
		mask = min_bit - 1;
		add.s0 = 0;
		add.s1 = min_bit;
		add.s2 = 0;
		if (((s.s1 & mask) == even)  && !s.s0)
		{
			if (s.s1 & min_bit)
			{
				s.s1 &= ~mask;
				s = add96(s, add);
			}
			else
			{
				s.s1 &= ~mask;
				s.s0 = 0;
			}
		}
		else if (s.s1 & even) // 大きいとき
		{
			s.s1 &= ~mask;
			s = add96(s, add);
		}
		else
		{
			s.s1 &= ~mask;
			s.s0 = 0;
		}
	}
	return (s);
}

char*			skip_white_space(char *str, int *state)
{
	if (isspace(*str))
	{
		*state = FSM_WS;
		return (++str);
	}
	*state = FSM_SON;
	return (str);
}

char*			sign_of_number(char *str, t_prep_number *pn, int *state)
{
	if (*str == '-' || *str == '+')
	{
		pn->negative = (*str == '-') ? 1 : 0;
		*state = FSM_LZOM;
		return (++str);
	}
	else if (isdigit(*str))
	{
		*state = FSM_LZOM;
		return (str);
	}
	*state = FSM_STOP;
	return (str);
}

char*			leading_zero_of_mantissa(char *str, int *state)
{
	if (*str == '0')
		return (++str);
	if (*str == '.')
	{
		*state = FSM_LZOF;
		return (++str);
	}
	*state = FSM_MIP;
	return (str);
}

char*			leading_zero_of_frac(char *str, t_prep_number *pn, int *state)
{
	if (*str == '0')
	{
		if (pn->exponent > -2147483648)
			pn->exponent--;
		return (++str);
	}
	*state = FSM_MFP;
	return (str);
}

char*			mantissa_int_part(char *str, t_prep_number *pn, int *state, int *digix)
{
	if (isdigit(*str))
	{
		if (*digix < DIGITS)
		{
			pn->mantissa = pn->mantissa * 10 + (*str - '0');
			(*digix)++;
		}
		else if (pn->exponent < 2147483647)
			pn->exponent++;
		return (++str);
	}
	if (*str == '.')
	{
		*state = FSM_MFP;
		return (++str);
	}
	*state = FSM_MFP;
	return (str);
}

char*			mantissa_frac_part(char *str, t_prep_number *pn, int *state, int *digix)
{
	if (isdigit(*str))
	{
		if (*digix < DIGITS)
		{
			pn->mantissa = pn->mantissa * 10 + (*str - '0');
			pn->exponent--;
			(*digix)++;
		}
		return (++str);
	}
	if (*str == 'e' || *str == 'E')
	{
		*state = FSM_ES;
		return (++str);
	}
	*state = FSM_ES;
	return (str);
}

char*			exponent_sign(char *str, int *state, int *exneg)
{
	if (*str == '+' || *str == '-')
	{
		*exneg = (*str == '-') ? 1 : 0;
		*state = FSM_ELZ;
		return (++str);
	}
	*state = FSM_ELZ;
	return (str);
}

char*			exponent_leading_zeros(char *str, int *state)
{
	if (*str == '0')
		return (++str);
	*state = FSM_E;
	return (str);
}

char*			exponent(char *str, int *expexp, int *state)
{
	if (isdigit(*str))
	{
		if (*expexp <= 2147483647 - (*str - '0') / 10)
			*expexp = *expexp * 10 + (*str - '0');
		else
			*expexp = 2147483647;
		return (++str);
	}
	*state = FSM_STOP;
	return (str);
}

static int	parse(char *str, t_prep_number *pn)
{
	int	state;
	int	digix;
	int	exneg;
	int	expexp;
	int	result;

	state = FSM_WS;
	digix = 0;
	exneg = 0;
	expexp = 0;
	result = PARSER_OK;
	while (state != FSM_STOP)
	{
		// skip white space
		if (state == FSM_WS)
			str = skip_white_space(str, &state);
			// read sign
		else if (state == FSM_SON)
			str = sign_of_number(str, pn, &state);
		else if (state == FSM_LZOM)
			str = leading_zero_of_mantissa(str, &state);
		else if (state == FSM_LZOF)
			str = leading_zero_of_frac(str, pn, &state);
		else if (state == FSM_MIP)
			str = mantissa_int_part(str, pn, &state, &digix);
		else if (state == FSM_MFP)
			str = mantissa_frac_part(str, pn, &state, &digix);
		else if (state == FSM_ES)
			str = exponent_sign(str, &state, &exneg);
		else if (state == FSM_ELZ)
			str = exponent_leading_zeros(str, &state);
		else if (state == FSM_E)
			str = exponent(str, &expexp, &state);
		else
			break;
	}
	if (exneg) expexp = -expexp;
	pn->exponent += expexp;

	if (pn->mantissa == 0)
	{
		if (pn->negative)
			result = PARSER_MZERO;
		else
			result = PARSER_PZERO;
	}
	else if (pn->exponent > 309)
	{
		if (pn->negative)
			result = PARSER_MINF;
		else
			result = PARSER_PINF;
	}
	else if (pn->exponent < -340)
	{
		if (pn->negative)
			result = PARSER_MZERO;
		else
			result = PARSER_PZERO;
	}
	return (result);
}

static double converter(t_prep_number *pn)
{
	int				binexp;
	uint64_t		binexs2;
	t_hex_double	hd;
	t_bit96			s;
	t_bit96			q;
	t_bit96			r;
	uint64_t		t;
	uint32_t		mask28;
	uint32_t		mask29;
	uint32_t		mask20;
	int				bit;

	binexp = 92;
	mask28 = 0xF << 28;
	mask29 = 0xE << 28;
	mask20 = 0xFFF << 20;
	// sign, exp, mantissa
	// mantissa to 96bit
	s.s2 = 0;
	s.s1 = (uint32_t)(pn->mantissa >> 32);
	s.s0 = (uint32_t)(pn->mantissa & 0xffffffff);
	hd.u = DOUBLE_PLUS_ZERO;
	while (pn->exponent > 0)
	{
		// mantissa * 10 = mantissa * (2 + 2^3)
		q = lsl96(s); // mantissa << 1
		r = lsl96(q); // mantissa << 2
		s = lsl96(r); // mantissa << 3
		s = add96(s, q); // mantissa * (2 + 2^3)
		pn->exponent--;

		while (s.s2 & mask28)
		{
			binexp++;
			s = lsr96(s);
		}
	}

	while (pn->exponent < 0)
	{
		while (!(s.s2 & (1 << 31)))
		{
			s = lsl96(s);
			binexp--;
		}
		q.s2 = s.s2 / 10;
		r.s1 = s.s2 % 10;
		r.s2 = (r.s1 << 24) | (s.s1 >> 8);
		q.s1 = r.s2 / 10;
		r.s1 = r.s2 % 10;
		r.s2 = (r.s1 << 24) | ((s.s1 & 0xFF) << 16) | (s.s0 >> 16);
		r.s0 = r.s2 / 10;
		r.s1 = r.s2 % 10;
		q.s0 = ((r.s1 << 16)| (s.s0 & 0xFFFF)) / 10 | (r.s0 << 16);
		q.s1 = ((r.s0 & 0x00FF0000) >> 16) | (q.s1 << 8);
		s.s2 = q.s2;
		s.s1 = q.s1;
		s.s0 = q.s0;

		pn->exponent++;
	}

	if (s.s2 || s.s1 || s.s0)
	{
		while (!(s.s2 & mask28))
		{
			s = lsl96(s);
			binexp--;
		}
	}
	binexp += 1023;
	//printf("binexp: %d\n", binexp);
	//printf("manttissa: %#x, %#x, %#x\n", s.s2, s.s1, s.s0);

	if (binexp > 2046)
	{
		if (pn->negative)
			hd.u = DOUBLE_MINUS_INFINITY;
		else
			hd.u = DOUBLE_PLUS_INFINITY;
	}
	else if (binexp < -52)
	{
		if (pn->negative)
			hd.u = DOUBLE_MINUS_ZERO;
	}
		// 非正規化数
	else if (binexp >= -52 && binexp < 1)
	{
		hd.u = 0;
		bit = binexp + 56;
		s = round_ties_even(s, bit);
		s = lsr96_bit(s, 64 - bit + 1);
		hd.u = (uint64_t)s.s1 | ((uint64_t)(s.s2 & ~mask20) << 32);
		if (pn->negative)
			hd.u |= (1ULL << 63);
	}
	else if (s.s2)
	{
		binexs2 = (uint64_t)binexp;
		// 完全に等しい時
		bit = 7;
		if (s.s1 & (1 << bit) && (!(s.s1 & ((1 << bit) - 1)) && !(s.s0)))
		{
			if ((s.s1 >> (bit + 1)) & 1)
				t = (s.s1 >> (bit + 1)) + 1; // 偶数方向に1足す
			else
				t = (s.s1 >> (bit + 1)); // すでに最下位ビットが0
		}
		else if (!(s.s1 & (1 << bit))) // 0x10000000のビットが立ってない時は切り捨てればよい
			t = (s.s1 >> (bit + 1));
			// 下位40ビットが0x10000000 00000000000000000000000000000000より大きい場合s1のビットを一つ大きくする
		else
			t = (s.s1 >> (bit + 1)) + 1;
		hd.u = (binexs2 << 52) | ((uint64_t)(s.s2 & ~mask28) << 24) | t;
		if (pn->negative)
			hd.u |= (1ULL << 63);
	}

	return hd.d;
}

double	ft_strtod(char *s)
{
	t_prep_number	*pn;
	t_hex_double	hd;
	int				i;
	double			result;

	hd.u = DOUBLE_PLUS_ZERO;
	pn = calloc(1, sizeof(t_prep_number));
	i = parse(s, pn);
	if (i == PARSER_OK)
		result = converter(pn);
	else if (i == PARSER_PZERO)
		result = hd.d;
	else if (i == PARSER_MZERO)
		result = DOUBLE_MINUS_ZERO;
	else if (i == PARSER_PINF)
		result = DOUBLE_PLUS_INFINITY;
	else if (i == PARSER_MINF)
		result = DOUBLE_MINUS_INFINITY;
	return (result);
}

int test(const char *str, int no, int *res_ret, int *res_end)
{
	double	ft_ret;
	double  lib_ret;

	double 	epsilon = 1e-12;

	char	*ft_end = NULL;
	char	*lib_end = NULL;

	bool	is_lib_of = false;
	bool	res_ok = false;
	bool	test_ret = false;
	bool	test_endptr = false;

	char	*color_start = "\x1b[31m";
	char	*color_end = "\x1b[0m";
	char	*OK = "\x1b[32mOK\x1b[0m";
	char	*NG = "\x1b[31mNG\x1b[0m";
	char	*lib_of;

	memset(&ft_ret, 0, sizeof(double));
	memset(&lib_ret, 0, sizeof(double));

	ft_ret = ft_strtod((char *)str);

	errno = 0;
	lib_ret = strtod(str, &lib_end);
	if (errno == ERANGE)
		is_lib_of = true;

	lib_of = is_lib_of ? "OF" : "";

	/* return value */
	test_ret = fabs(ft_ret - lib_ret) < epsilon ? true : false;
	if (ft_ret == INFINITY && lib_ret == INFINITY)
		test_ret = true;

	/* endptr */
//	test_endptr = (strcmp(ft_end, lib_end) == 0) ? true : false;
	test_endptr = true;
	if (test_ret && test_endptr)
	{
		res_ok = true;
		color_start = "\x1b[32m";
	}

	printf("%s"
		   "[%03d:%s] input   =    %s\n"
		   "         ft_ret  = %%f[%f],     endptr[%s]\n"
		   "         lib_ret = %%f[%f],     endptr[%s],     ERANGE:%s\n"
		   "         d_ret   = %%e[%e],  %%f[%f]"
		   "%s\n"
		   "   RESULT : return value=%s,  endptr=%s\n",
		   color_start,
		   no, res_ok ? "OK" : "WA", str,
		   ft_ret, ft_end,
		   lib_ret, lib_end, lib_of,
		   ft_ret - lib_ret, ft_ret - lib_ret,
		   color_end,
		   test_ret ? OK : NG,
		   test_endptr ? OK : NG);
	print_float_bit(ft_ret,  "   bit:ft  = ");
	print_float_bit(lib_ret, "   bit:lib = ");
	printf("\n");

	*res_ret += test_ret;
	*res_end += test_endptr;
	return (res_ok);
}

int main(void)
{
	int	ok;
	int test_no;
	int	res_ret = 0;
	int res_end = 0;

	printf("############ TEST ############\n");

	ok = 0;
	test_no = 0;
	ok += test("1", ++test_no, &res_ret, &res_end);
	ok += test("2147483647", ++test_no, &res_ret, &res_end);
	ok += test("-2147483648", ++test_no, &res_ret, &res_end);
	ok += test("9223372036854775807", ++test_no, &res_ret, &res_end);
	ok += test("-9223372036854775808", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("1.0", ++test_no, &res_ret, &res_end);
	ok += test("-1.0", ++test_no, &res_ret, &res_end);
	ok += test("0.1", ++test_no, &res_ret, &res_end);
	ok += test("0.01", ++test_no, &res_ret, &res_end);
	ok += test("0.001", ++test_no, &res_ret, &res_end);
	ok += test("0.0001", ++test_no, &res_ret, &res_end);
	ok += test("0.00001", ++test_no, &res_ret, &res_end);
	ok += test("0.000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.00000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("0.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("1.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("10.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("100.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("1000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("10000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("100000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("1000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("10000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("100000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("1000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("10000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("100000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("1000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("10000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);
	ok += test("100000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("0.00000000000000000019", ++test_no, &res_ret, &res_end);
	ok += test("0.1001001001001001", ++test_no, &res_ret, &res_end);
	ok += test("-1.0000001", ++test_no, &res_ret, &res_end);
	ok += test("-1.00000001", ++test_no, &res_ret, &res_end);
	ok += test("-1.000000001", ++test_no, &res_ret, &res_end);
	ok += test("1.00000001", ++test_no, &res_ret, &res_end);
	ok += test("1.000000001", ++test_no, &res_ret, &res_end);
	ok += test("1.0000000001", ++test_no, &res_ret, &res_end);
	ok += test("1.00000000010000000000", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("3.14", ++test_no, &res_ret, &res_end);
	ok += test("3.141", ++test_no, &res_ret, &res_end);
	ok += test("3.1415", ++test_no, &res_ret, &res_end);
	ok += test("3.14159", ++test_no, &res_ret, &res_end);
	ok += test("3.141592", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832795", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327950", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279502", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832795028", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327950288", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279502884", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832795028841", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327950288419", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279502884197", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832795028841971", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327950288419716", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279502884197169", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832795028841971693", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327950288419716939", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279502884197169399", ++test_no, &res_ret, &res_end);
	ok += test("3.1415926535897932384626433832795028841971693993", ++test_no, &res_ret, &res_end);
	ok += test("3.14159265358979323846264338327950288419716939937", ++test_no, &res_ret, &res_end);
	ok += test("3.141592653589793238462643383279502884197169399375", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test(".1415", ++test_no, &res_ret, &res_end);
	ok += test("--1.0", ++test_no, &res_ret, &res_end);
	ok += test("1..0", ++test_no, &res_ret, &res_end);
	ok += test("-.5", ++test_no, &res_ret, &res_end);
	ok += test(".", ++test_no, &res_ret, &res_end);
	ok += test("-", ++test_no, &res_ret, &res_end);
	ok += test("--", ++test_no, &res_ret, &res_end);
	ok += test("+", ++test_no, &res_ret, &res_end);
	ok += test("++", ++test_no, &res_ret, &res_end);
	ok += test("-.", ++test_no, &res_ret, &res_end);

	ok += test("..", ++test_no, &res_ret, &res_end);
	ok += test(".E", ++test_no, &res_ret, &res_end);
	ok += test(".e-", ++test_no, &res_ret, &res_end);
	ok += test(".e.", ++test_no, &res_ret, &res_end);

	ok += test("10.", ++test_no, &res_ret, &res_end);
	ok += test(".0005", ++test_no, &res_ret, &res_end);
	ok += test(".10.10", ++test_no, &res_ret, &res_end);

	ok += test("12.3E+45", ++test_no, &res_ret, &res_end);
	ok += test("12.3E-45", ++test_no, &res_ret, &res_end);
	ok += test("12.3E-4.5", ++test_no, &res_ret, &res_end);
	ok += test("12.3E--45", ++test_no, &res_ret, &res_end);
	ok += test("12.3E-45E-5", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("123.456E6", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-6", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-5", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-4", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-3", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-2", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-1", ++test_no, &res_ret, &res_end);

	ok += test("123.45e1", ++test_no, &res_ret, &res_end);
	ok += test("123.45e12", ++test_no, &res_ret, &res_end);
	ok += test("123.45e123", ++test_no, &res_ret, &res_end);
	ok += test("123.45e1234", ++test_no, &res_ret, &res_end);
	ok += test("123.45e12345", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-1", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-12", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-123", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-1234", ++test_no, &res_ret, &res_end);
	ok += test("123.45e-12345", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("2147483646", ++test_no, &res_ret, &res_end);
	ok += test("2147483647", ++test_no, &res_ret, &res_end);
	ok += test("2147483648", ++test_no, &res_ret, &res_end);
	ok += test("2147483649", ++test_no, &res_ret, &res_end);

	ok += test("9223372036854775807", ++test_no, &res_ret, &res_end);
	ok += test("9223372036854775808", ++test_no, &res_ret, &res_end);

	ok += test("18446744073709551614", ++test_no, &res_ret, &res_end);
	ok += test("18446744073709551615", ++test_no, &res_ret, &res_end);
	ok += test("18446744073709551616", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("1234567890", ++test_no, &res_ret, &res_end);
	ok += test("12345678901", ++test_no, &res_ret, &res_end);
	ok += test("123456789012", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012345", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012345678", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890", ++test_no, &res_ret, &res_end);

	//この辺りから怪しい
	ok += test("1234567890123456789012345678901", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890123", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012345678901234", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890123456", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012345678901234567", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345678", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890123456789", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("1234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
//	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890E+10000", ++test_no, &res_ret, &res_end);

//	ok += test("1.0E+10", ++test_no, &res_ret, &res_end);
//	ok += test("1.0E+50", ++test_no, &res_ret, &res_end);
//	ok += test("1.0E+100", ++test_no, &res_ret, &res_end);
//	ok += test("1.0E+150", ++test_no, &res_ret, &res_end);
//	ok += test("1.0E+200", ++test_no, &res_ret, &res_end);
//	ok += test("1.0E+250", ++test_no, &res_ret, &res_end);
//	ok += test("1.0E+300", ++test_no, &res_ret, &res_end);


	printf(" ## RESULT ##\n");
	printf("     OK: %d, NG: %d\n", ok, test_no - ok);
	printf("     retNG:%d, errNG:%d\n\n", test_no - res_ret, test_no - res_end);



	test("123456789012345678901", ++test_no, &res_ret, &res_end);



	print_float_bit(2147483647.9999995, "2147483647.9999995");
	print_float_bit(2147483647.9999996, "2147483647.9999996");
	print_float_bit(2147483647.9999997, "2147483647.9999997");
	print_float_bit(2147483647.9999998, "2147483647.9999998");
	print_float_bit(2147483647.9999999, "2147483647.9999999");
	print_float_bit(2147483648.0000000, "2147483648.0000000");
	print_float_bit(2147483648.0,       "2147483648.0");



	return (0);
}

void	print_float_bit(double double_num, char *str)
{
	union lld_union
	{
		long long	ll;
		double 		d;
	};

	union lld_union	lld;
	memset(&lld, 0, sizeof(union lld_union));

	lld.d = double_num;
//	printf("%s double:%f -> [", str, lld.d);
	printf("%s [", str);

	int shift = 63;
	while (shift >= 0)
	{
		printf("%lld", (lld.ll >> shift) & 1);
		if (shift == 63 || shift == 52)
			printf(" ");
		shift--;
	}
	printf("]\n");
}


//2147483647
//4294967295
//9223372036854775807
//18446744073709551615



// 1234567890123456789012345678901234567890 input
//  vv 桁数はOK
// 1234567890123456800000000000000000000000 sim
// 1234567890123456846996462118072609669120.000000 lib
// 1234567890123456846996462118072609669120.000000 lib memset(0)






