/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/25 12:00:59 by takira           ###   ########.fr       */
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

//double	ft_strtod(const char *str, bool *is_success)
//{
//	double	ret_num;
//	double 	scale;
//	double 	sign;
//	size_t	idx;
//
//	idx = 0;
//	sign = 1;
//	*is_success = false;
//	if (!str)
//		return (0);
//
//	ret_num = 0.0;
//	while (isspace(str[idx]))
//		idx++;
//	if (str[idx] == '-')
//			sign = -1;
//	if (str[idx] == '-' || str[idx] == '+')
//		idx++;
//	while ('0' <= str[idx] && str[idx] <= '9')
//	{
//		ret_num = ret_num * 10 + str[idx] - '0';
//		idx++;
//	}
//	if (str[idx] == '.')
//		idx++;
//	scale = 10.0;
//	while ('0' <= str[idx] && str[idx] <= '9')
//	{
//		ret_num += (double)(str[idx] - '0') / scale;
//		scale *= 10.0;
//		idx++;
//	}
//	if (!str[idx])
//		*is_success = true;
//	return (sign * ret_num);
//}

#define SUCCESS	0
#define FAILURE	1

static int get_num_part(const char *str, double *num, double *sign, size_t *idx)
{
	double	scale;
	size_t 	i;

	i = 0;
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
	while ('0' <= str[*idx] && str[*idx] <= '9')
	{
		*num = *num * 10 + str[*idx] - '0';
		*idx += 1;
	}
	if (str[*idx] == '.')
	{
		*idx += 1;
		scale = 0.1;
		while ('0' <= str[*idx] && str[*idx] <= '9')
		{
			*num += (double)(str[*idx] - '0') * scale;
			scale *= 0.1;
			*idx += 1;
		}
	}
	return (SUCCESS);
}

static int	get_exp_part(const char *str, double *num, size_t *idx)
{
	double 	exp;
	double 	exp_sign;
	size_t 	i;

	exp = 0.0;
	exp_sign = 1.0;
	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
		return (SUCCESS);
	i = 1;
	if (!str[*idx + i])
		return (FAILURE);
	if (str[*idx + 1] == '-')
		exp_sign = -1.0;
	if (str[*idx + i] == '-' || str[*idx + i] == '+')
		i++;
	if (!str[*idx + i] || !isdigit(str[*idx + i]))
		return (FAILURE);
	while ('0' <= str[*idx + i] && str[*idx + i] <= '9')
	{
		exp = exp * 10 + str[*idx + i] - '0';
		i++;
	}
	*num *= pow(10, exp * exp_sign);
	*idx += i;
	return (SUCCESS);
}

double	ft_strtod(const char *str, bool *is_success, char **err)
{
	double	num;
	double 	num_sign;
	size_t	idx;

	idx = 0;
	num = 0.0;
	num_sign = 1.0;
	*is_success = false;
	if (!str)
	{
		*err = (char *)&str[idx];
		return (num);
	}
	if (get_num_part(str, &num, &num_sign, &idx) == FAILURE)
	{
		*err = (char *)&str[idx];
		return (num);
	}
	if (get_exp_part(str, &num, &idx) == FAILURE)
	{
		*err = (char *)&str[idx];
		return (num_sign * num);
	}
	if (!str[idx])
		*is_success = true;
	*err = (char *)&str[idx];
	return (num_sign * num);
}

int test(const char *str, int no, int *res_ret, int *res_err, int *res_flg)
{
	double	ft_ret, lib_ret;
	bool	ft_is_success;
	char	*ft_err = NULL;
	char	*lib_err = NULL;
	bool	res_ok;
	char	*color_start = "\x1b[31m";
	char	*color_end = "\x1b[0m";
	bool	test_ret, test_flg, test_err;
	char	*OK = "\x1b[32mOK\x1b[0m";
	char	*NG = "\x1b[31mNG\x1b[0m";

	ft_ret = ft_strtod(str, &ft_is_success, &ft_err);
	lib_ret = strtod(str, &lib_err);

	res_ok = false;

	test_ret = (ft_ret == lib_ret) ? true : false;
	test_err = (strcmp(ft_err, lib_err) == 0) ? true : false;
	test_flg = ((ft_is_success && strlen(lib_err) == 0) || (!ft_is_success && strlen(lib_err) != 0)) ? true : false;

	if (test_ret && test_err && test_flg)
	{
		res_ok = true;
		color_start = "\x1b[32m";
	}
	printf("%s"
		   "[%03d:%s] input   = %s\n"
		   "         ft_ret  = %%e[%e],  %%f[%f],     err[%s],     is_success[%s]\n"
		   "         lib_ret = %%e[%e],  %%f[%f],     err[%s]"
		   "%s\n"
		   "         return value:ft==lib:%s,  err char:ft==lib:%s,  ft_is_success:%s\n\n",
		   color_start, no, res_ok ? "OK" : "WA", str,
		   ft_ret, ft_ret, ft_err, ft_is_success ? "true" : "false",
		   lib_ret, lib_ret, lib_err,
		   color_end,
		   test_ret ? OK : NG, test_err ? OK : NG, test_flg ? OK : NG);

	*res_ret += test_ret;
	*res_err += test_err;
	*res_flg += test_flg;
	return (res_ok);
}

int main(void)
{
	int	ok;
	int test_no;
	int	res_ret = 0;
	int res_err = 0;
	int res_flg = 0;

	printf("############ TEST ############\n");

	ok = 0;
	test_no = 0;
	ok += test("1", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("2147483647", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-2147483648", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("9223372036854775807", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-9223372036854775808", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1.0", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-1.0", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.1", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.01", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("10.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("100.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("10000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("100000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("10000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("100000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("10000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("100000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("10000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("100000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.00000000000000000019", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("0.1001001001001001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-1.0000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-1.00000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-1.000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1.00000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1.000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1.0000000001", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1.00000000010000000000", ++test_no, &res_ret, &res_err, &res_flg);

	ok += test("3.14", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832795", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327950", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279502", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832795028", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327950288", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279502884", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832795028841", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327950288419", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279502884197", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832795028841971", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327950288419716", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279502884197169", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832795028841971693", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327950288419716939", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279502884197169399", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.1415926535897932384626433832795028841971693993", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.14159265358979323846264338327950288419716939937", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("3.141592653589793238462643383279502884197169399375", ++test_no, &res_ret, &res_err, &res_flg);


	ok += test(".1415", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("--1.0", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("1..0", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-.5", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test(".", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("--", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("+", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("++", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("-.", ++test_no, &res_ret, &res_err, &res_flg);

	ok += test("..", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test(".E", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test(".e-", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test(".e.", ++test_no, &res_ret, &res_err, &res_flg);

	ok += test("10.", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test(".0005", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test(".10.10", ++test_no, &res_ret, &res_err, &res_flg);

	ok += test("12.3E+45", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("12.3E-45", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("12.3E-4.5", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("12.3E--45", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("12.3E-45E-5", ++test_no, &res_ret, &res_err, &res_flg);

	ok += test("123.456E6", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-6", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-5", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-4", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-3", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-2", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-1", ++test_no, &res_ret, &res_err, &res_flg);

	ok += test("123.45e1", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e12", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e123", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e1234", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e12345", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-1", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-12", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-123", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-1234", ++test_no, &res_ret, &res_err, &res_flg);
	ok += test("123.45e-12345", ++test_no, &res_ret, &res_err, &res_flg);



	printf(" ## RESULT ##\n");
	printf("     OK: %d, NG: %d\n", ok, test_no - ok);
	printf("     retNG:%d, errNG:%d, flgNG:%d\n\n", test_no - res_ret, test_no - res_err, test_no - res_flg);
}
