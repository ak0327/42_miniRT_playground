/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/26 11:36:44 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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



//static int get_num_part(const char *str, double *num, double *sign, size_t *idx)
//{
//	double	scale;
//	size_t 	i;
//
//	i = 0;
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
//double	ft_strtod(const char *str, bool *is_success, char **err)
//{
//	double	num;
//	double 	num_sign;
//	size_t	idx;
//
//	idx = 0;
//	num = 0.0;
//	num_sign = 1.0;
//	*is_success = false;
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
//	if (!str[idx])
//		*is_success = true;
//	*err = (char *)&str[idx];
//	return (num_sign * num);
//}



/* IEEE754準拠 */

typedef struct s_prep_number
{
	int 		sign;
	int32_t 	exponent;
	uint64_t	mantissa;
}				t_prep_number;

//int	parsing_integer_part(const char *str, size_t *idx, t_prep_number *prep_num)
//{
//	*idx = 0;
//	while (isspace(str[*idx]))
//		*idx += 1;
//	if (!str[*idx])
//		return (FAILURE);
//	if (str[*idx] == '-')
//		prep_num->sign = -1;
//	if (str[*idx] == '-' || str[*idx] == '+')
//		*idx += 1;
//	while (isdigit(str[*idx]))
//	{
//		prep_num->mantissa = prep_num->mantissa * 10 + str[*idx] - '0';
//		*idx += 1;
//	}
//	if (!str[*idx])
//		return (SUCCESS);
//	return (SUCCESS);
//}
//
//int	parsing_fractional_part(const char *str, size_t *idx, t_prep_number *prep_num)
//{
//	if (str[*idx] == '.')
//		*idx += 1;
//	if (!(!str[*idx] || isdigit(str[*idx]) || str[*idx] == 'e' || str[*idx] == 'E'))
//		return (FAILURE);
//	while (isdigit(str[*idx]))
//	{
//		prep_num->mantissa = prep_num->mantissa * 10 + str[*idx] - '0';
//		prep_num->exponent--;
//		*idx += 1;
//	}
//	return (SUCCESS);
//}
//
//int	parsing_exponential_part(const char *str, size_t *idx, t_prep_number *prep_num)
//{
//	int		sign;
//	int32_t	exp;
//
//	sign = 1;
//	exp = 0;
//	if (!(str[*idx] == 'e' || str[*idx] == 'E'))
//		return (SUCCESS);
//	if (str[*idx] == '-')
//		sign = -1;
//	if (str[*idx] == '+' || str[*idx] == '-')
//		*idx += 1;
//	if (!str[*idx] || !isdigit(str[*idx]))
//		return (FAILURE);
//	while (isdigit(str[*idx]))
//	{
//		exp = exp * 10 + str[*idx] - '0';
//		*idx += 1;
//	}
//	prep_num->exponent += sign * exp;
//	if (str[*idx])
//		return (FAILURE);
//	return (SUCCESS);
//}
//




static int get_num_part(const char *str, uint64_t *n, double *sign, size_t *idx, long *exp)
{
	size_t 		i;
	int 		digit;

	*n = 0;
	*exp = 0;
	while (isspace(str[*idx]))
		*idx += 1;
	if (str[*idx] == '-')
		*sign = -1.0;
	i = 0;
	if (str[*idx + i] == '-' || str[*idx + i] == '+')
		i++;
	if (!str[*idx + i] || !(isdigit(str[*idx + i]) || (str[*idx + i] == '.' && isdigit(str[*idx + i + 1]))))
		return (FAILURE);
	*idx += i;
	while (isdigit(str[*idx]))
	{
		digit = str[*idx] - '0';
		if (*n <= SIZE_MAX / 10)
			*n = *n * 10 + digit;
		else
			*exp += 1;
		*idx += 1;
	}
	printf("[get_num_part-1] n:%llo, exp:%ld\n", *n, *exp);
	if (str[*idx] == '.')
	{
		*idx += 1;
		while (isdigit(str[*idx]))
		{
			if (*n <= DBL_MAX / 10)
				*n = *n * 10 + str[*idx] - '0';
			else
				*exp += 1;
			*exp -= 1;
			*idx += 1;
		}
	}
	printf("[get_num_part-2] n:%llo, exp:%ld\n", *n, *exp);
	return (SUCCESS);
}

static int	get_exp_part(const char *str, size_t *idx, long *exp)
{
	bool	exp_negative;
	long 	exp_val;
	size_t 	i;

	exp_negative = false;
	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
		return (SUCCESS);
	i = 1;
	if (!str[*idx + i])
		return (FAILURE);
	if (str[*idx + 1] == '-')
		exp_negative = true;
	if (str[*idx + i] == '-' || str[*idx + i] == '+')
		i++;
	if (!str[*idx + i] || !isdigit(str[*idx + i]))
		return (FAILURE);
	while ('0' <= str[*idx + i] && str[*idx + i] <= '9')
	{
		if (exp_negative && exp_val < LONG_MIN / 10)
		{
			exp_val = LONG_MIN;
			break ;
		}
		else if (!exp_negative && exp_val > LONG_MAX / 10)
		{
			exp_val = LONG_MAX;
			break ;
		}
		if (exp_negative)
			exp_val = exp_val * 10 - (str[*idx + i] - '0');
		else
			exp_val = exp_val * 10 + (str[*idx + i] - '0');
		i++;
	}
	*exp = *exp + exp_val;
	printf("[get_exp_part] exp:%ld, exp_val:%ld\n", *exp, exp_val);
	*idx += i;
	return (SUCCESS);
}

double	get_double_fpn(uint64_t n, long exp)
{
	double	num;

	num = n * pow(10, exp);

	printf("[get_fpn]n:%lld, exp:%ld, num:%f\n", n, exp, num);
	return (num);
}

double	ft_strtod(const char *str, char **err)
{
	uint64_t	n;
	long 		exp;

	double	num;
	double 	num_sign;
	size_t	idx;

	idx = 0;
	num = 0.0;
	num_sign = 1.0;
	exp = 0;
	if (!str)
	{
		*err = (char *)&str[idx];
		return (num);
	}
	if (get_num_part(str, &n, &num_sign, &idx, &exp) == FAILURE)
	{
		*err = (char *)&str[idx];
		return (num);
	}
	if (get_exp_part(str,&idx, &exp) == FAILURE)
	{
		*err = (char *)&str[idx];
		return (num_sign * num);
	}

	num = get_double_fpn(n, exp);

	*err = (char *)&str[idx];
	return (num_sign * num);
}


int test(const char *str, int no, int *res_ret, int *res_err)
{
	double	ft_ret, lib_ret;
	char	*ft_err = NULL;
	char	*lib_err = NULL;
	bool	is_lib_of = false;

	bool	res_ok;

	char	*color_start = "\x1b[31m";
	char	*color_end = "\x1b[0m";
	bool	test_ret, test_err;
	char	*OK = "\x1b[32mOK\x1b[0m";
	char	*NG = "\x1b[31mNG\x1b[0m";
	double 	epsilon = 1e-12;

	ft_ret = ft_strtod(str, &ft_err);

	errno = 0;
	lib_ret = strtod(str, &lib_err);
	if (errno == ERANGE)
		is_lib_of = true;
	char	*lib_of = is_lib_of ? "OF" : "";

	res_ok = false;

	test_ret = fabs(ft_ret - lib_ret) < epsilon ? true : false;
	if (ft_ret == INFINITY && lib_ret == INFINITY)
		test_ret = true;
	test_err = (strcmp(ft_err, lib_err) == 0) ? true : false;
//	test_flg = ((ft_is_success && strlen(lib_err) == 0) || (!ft_is_success && strlen(lib_err) != 0)) ? true : false;

	//	if (test_ret && test_err && test_flg)
	if (test_ret && test_err)
	{
		res_ok = true;
		color_start = "\x1b[32m";
	}

	printf("%s"
		   "[%03d:%s] input   = %s\n"
		   "         ft_ret  = %%f[%f],     err[%s]\n"
		   "         lib_ret = %%f[%f],     err[%s],     of:%s\n"
		   "         d_ret   = %%e[%e],  %%f[%f]"
		   "%s\n"
		   "         return value:ft==lib:%s,  err char:ft==lib:%s\n",
		   color_start,
		   no, res_ok ? "OK" : "WA", str,
		   ft_ret, ft_err,
		   lib_ret, lib_err, lib_of,
		   ft_ret - lib_ret, ft_ret - lib_ret,
		   color_end,
		   test_ret ? OK : NG,
		   test_err ? OK : NG);

	*res_ret += test_ret;
	*res_err += test_err;
	return (res_ok);
}

int main(void)
{
	int	ok;
	int test_no;
	int	res_ret = 0;
	int res_err = 0;

	printf("############ TEST ############\n");

	ok = 0;
	test_no = 0;
	ok += test("1", ++test_no, &res_ret, &res_err);
	ok += test("2147483647", ++test_no, &res_ret, &res_err);
	ok += test("-2147483648", ++test_no, &res_ret, &res_err);
	ok += test("9223372036854775807", ++test_no, &res_ret, &res_err);
	ok += test("-9223372036854775808", ++test_no, &res_ret, &res_err);
	ok += test("1.0", ++test_no, &res_ret, &res_err);
	ok += test("-1.0", ++test_no, &res_ret, &res_err);
	ok += test("0.1", ++test_no, &res_ret, &res_err);
	ok += test("0.01", ++test_no, &res_ret, &res_err);
	ok += test("0.001", ++test_no, &res_ret, &res_err);
	ok += test("0.0001", ++test_no, &res_ret, &res_err);
	ok += test("0.00001", ++test_no, &res_ret, &res_err);
	ok += test("0.000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("1.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("10.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("100.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("1000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("10000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("100000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("1000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("10000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("100000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("1000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("10000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("100000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("1000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("10000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("100000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err);
	ok += test("0.00000000000000000019", ++test_no, &res_ret, &res_err);
	ok += test("0.1001001001001001", ++test_no, &res_ret, &res_err);
	ok += test("-1.0000001", ++test_no, &res_ret, &res_err);
	ok += test("-1.00000001", ++test_no, &res_ret, &res_err);
	ok += test("-1.000000001", ++test_no, &res_ret, &res_err);
	ok += test("1.00000001", ++test_no, &res_ret, &res_err);
	ok += test("1.000000001", ++test_no, &res_ret, &res_err);
	ok += test("1.0000000001", ++test_no, &res_ret, &res_err);
	ok += test("1.00000000010000000000", ++test_no, &res_ret, &res_err);

	ok += test("3.14", ++test_no, &res_ret, &res_err);
	ok += test("3.141", ++test_no, &res_ret, &res_err);
	ok += test("3.1415", ++test_no, &res_ret, &res_err);
	ok += test("3.14159", ++test_no, &res_ret, &res_err);
	ok += test("3.141592", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832795", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327950", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279502", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832795028", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327950288", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279502884", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832795028841", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327950288419", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279502884197", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832795028841971", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327950288419716", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279502884197169", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832795028841971693", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327950288419716939", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279502884197169399", ++test_no, &res_ret, &res_err);
	ok += test("3.1415926535897932384626433832795028841971693993", ++test_no, &res_ret, &res_err);
	ok += test("3.14159265358979323846264338327950288419716939937", ++test_no, &res_ret, &res_err);
	ok += test("3.141592653589793238462643383279502884197169399375", ++test_no, &res_ret, &res_err);


	ok += test(".1415", ++test_no, &res_ret, &res_err);
	ok += test("--1.0", ++test_no, &res_ret, &res_err);
	ok += test("1..0", ++test_no, &res_ret, &res_err);
	ok += test("-.5", ++test_no, &res_ret, &res_err);
	ok += test(".", ++test_no, &res_ret, &res_err);
	ok += test("-", ++test_no, &res_ret, &res_err);
	ok += test("--", ++test_no, &res_ret, &res_err);
	ok += test("+", ++test_no, &res_ret, &res_err);
	ok += test("++", ++test_no, &res_ret, &res_err);
	ok += test("-.", ++test_no, &res_ret, &res_err);

	ok += test("..", ++test_no, &res_ret, &res_err);
	ok += test(".E", ++test_no, &res_ret, &res_err);
	ok += test(".e-", ++test_no, &res_ret, &res_err);
	ok += test(".e.", ++test_no, &res_ret, &res_err);

	ok += test("10.", ++test_no, &res_ret, &res_err);
	ok += test(".0005", ++test_no, &res_ret, &res_err);
	ok += test(".10.10", ++test_no, &res_ret, &res_err);

	ok += test("12.3E+45", ++test_no, &res_ret, &res_err);
	ok += test("12.3E-45", ++test_no, &res_ret, &res_err);
	ok += test("12.3E-4.5", ++test_no, &res_ret, &res_err);
	ok += test("12.3E--45", ++test_no, &res_ret, &res_err);
	ok += test("12.3E-45E-5", ++test_no, &res_ret, &res_err);

	ok += test("123.456E6", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-6", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-5", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-4", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-3", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-2", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-1", ++test_no, &res_ret, &res_err);

	ok += test("123.45e1", ++test_no, &res_ret, &res_err);
	ok += test("123.45e12", ++test_no, &res_ret, &res_err);
	ok += test("123.45e123", ++test_no, &res_ret, &res_err);
	ok += test("123.45e1234", ++test_no, &res_ret, &res_err);
	ok += test("123.45e12345", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-1", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-12", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-123", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-1234", ++test_no, &res_ret, &res_err);
	ok += test("123.45e-12345", ++test_no, &res_ret, &res_err);

	ok += test("2147483646", ++test_no, &res_ret, &res_err);
	ok += test("2147483647", ++test_no, &res_ret, &res_err);
	ok += test("2147483648", ++test_no, &res_ret, &res_err);
	ok += test("2147483649", ++test_no, &res_ret, &res_err);

	ok += test("9223372036854775807", ++test_no, &res_ret, &res_err);
	ok += test("9223372036854775808", ++test_no, &res_ret, &res_err);

	ok += test("18446744073709551614", ++test_no, &res_ret, &res_err);
	ok += test("18446744073709551615", ++test_no, &res_ret, &res_err);
	ok += test("18446744073709551616", ++test_no, &res_ret, &res_err);

	ok += test("1234567890", ++test_no, &res_ret, &res_err);
	ok += test("12345678901", ++test_no, &res_ret, &res_err);
	ok += test("123456789012", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012345", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012345678", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890", ++test_no, &res_ret, &res_err);

	//この辺りから怪しい
	ok += test("1234567890123456789012345678901", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789012", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012345678901234", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789012345", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123456", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012345678901234567", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789012345678", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123456789", ++test_no, &res_ret, &res_err);

	ok += test("1234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_err);
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890E+10000", ++test_no, &res_ret, &res_err);

	ok += test("1.0E+10", ++test_no, &res_ret, &res_err);
	ok += test("1.0E+50", ++test_no, &res_ret, &res_err);
	ok += test("1.0E+100", ++test_no, &res_ret, &res_err);
	ok += test("1.0E+150", ++test_no, &res_ret, &res_err);
	ok += test("1.0E+200", ++test_no, &res_ret, &res_err);
	ok += test("1.0E+250", ++test_no, &res_ret, &res_err);
	ok += test("1.0E+300", ++test_no, &res_ret, &res_err);


	printf(" ## RESULT ##\n");
	printf("     OK: %d, NG: %d\n", ok, test_no - ok);
	printf("     retNG:%d, errNG:%d\n\n", test_no - res_ret, test_no - res_err);

	printf("double_max:%e\n", DBL_MAX);
	printf("double_min:%e\n", DBL_MIN);
	return (0);
}
//2147483647
//4294967295
//9223372036854775807
//18446744073709551615

