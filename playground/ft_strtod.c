/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 18:51:27 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

double	ft_strtod(const char *str, bool *is_success)
{
	double	ret_num;
	double 	scale;
	double 	sign;
	size_t	idx;

	idx = 0;
	sign = 1;
	*is_success = false;
	if (!str)
		return (0);

	ret_num = 0.0;
	while (isspace(str[idx]))
		idx++;
	if (str[idx] == '-')
			sign = -1;
	if (str[idx] == '-' || str[idx] == '+')
		idx++;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		ret_num = ret_num * 10 + str[idx] - '0';
		idx++;
	}
	if (str[idx] == '.')
		idx++;
	scale = 10.0;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		ret_num += (double)(str[idx] - '0') / scale;
		scale *= 10.0;
		idx++;
	}
	if (!str[idx])
		*is_success = true;
	return (sign * ret_num);
}

int test(const char *str, int no)
{
	double	ft_ret, lib_ret;
	bool	ft_is_success;
	char	*lib_err = NULL;
	bool	ok;

	ft_ret = ft_strtod(str, &ft_is_success);
	lib_ret = strtod(str, &lib_err);

	ok = false;
	if (ft_ret == lib_ret)
//	if (ft_is_success && !lib_err)
		ok = true;

	printf("[%02d] s=%55s,  ft=% e,  lib=% e,  ret=%s\n", no, str, ft_ret, lib_ret, ok ? "\x1b[32mAC\x1b[0m" : "\x1b[31mWA\x1b[0m");
	if (ok)
		return (1);
	return (0);
}

int main(void)
{
	int	ok;
	int test_no;

	printf("############ TEST ############\n");

	ok = 0;
	test_no = 0;
	ok += test("1", ++test_no);
	ok += test("2147483647", ++test_no);
	ok += test("-2147483648", ++test_no);
	ok += test("9223372036854775807", ++test_no);
	ok += test("-9223372036854775808", ++test_no);
	ok += test("1.0", ++test_no);
	ok += test("-1.0", ++test_no);
	ok += test("0.1", ++test_no);
	ok += test("0.01", ++test_no);
	ok += test("0.001", ++test_no);
	ok += test("0.0001", ++test_no);
	ok += test("0.00001", ++test_no);
	ok += test("0.000001", ++test_no);
	ok += test("0.0000001", ++test_no);
	ok += test("0.00000001", ++test_no);
	ok += test("0.000000001", ++test_no);
	ok += test("0.0000000001", ++test_no);
	ok += test("0.00000000001", ++test_no);
	ok += test("0.000000000001", ++test_no);
	ok += test("0.0000000000001", ++test_no);
	ok += test("0.00000000000001", ++test_no);
	ok += test("0.000000000000001", ++test_no);
	ok += test("0.0000000000000001", ++test_no);
	ok += test("0.00000000000000001", ++test_no);
	ok += test("0.000000000000000001", ++test_no);
	ok += test("0.0000000000000000001", ++test_no);
	ok += test("0.00000000000000000001", ++test_no);
	ok += test("0.000000000000000000001", ++test_no);
	ok += test("0.0000000000000000000001", ++test_no);
	ok += test("0.00000000000000000000001", ++test_no);
	ok += test("0.000000000000000000000001", ++test_no);
	ok += test("0.0000000000000000000000001", ++test_no);
	ok += test("0.00000000000000000000000001", ++test_no);
	ok += test("0.000000000000000000000000001", ++test_no);
	ok += test("0.0000000000000000000000000001", ++test_no);
	ok += test("1.0000000000000000000000000001", ++test_no);
	ok += test("10.0000000000000000000000000001", ++test_no);
	ok += test("100.0000000000000000000000000001", ++test_no);
	ok += test("1000.0000000000000000000000000001", ++test_no);
	ok += test("10000.0000000000000000000000000001", ++test_no);
	ok += test("100000.0000000000000000000000000001", ++test_no);
	ok += test("1000000.0000000000000000000000000001", ++test_no);
	ok += test("10000000.0000000000000000000000000001", ++test_no);
	ok += test("100000000.0000000000000000000000000001", ++test_no);
	ok += test("1000000000.0000000000000000000000000001", ++test_no);
	ok += test("10000000000.0000000000000000000000000001", ++test_no);
	ok += test("100000000000.0000000000000000000000000001", ++test_no);
	ok += test("1000000000000.0000000000000000000000000001", ++test_no);
	ok += test("10000000000000.0000000000000000000000000001", ++test_no);
	ok += test("100000000000000.0000000000000000000000000001", ++test_no);
	ok += test("0.00000000000000000019", ++test_no);
	ok += test("0.1001001001001001", ++test_no);
	ok += test("-1.0000001", ++test_no);
	ok += test("-1.00000001", ++test_no);
	ok += test("-1.000000001", ++test_no);
	ok += test("1.00000001", ++test_no);
	ok += test("1.000000001", ++test_no);
	ok += test("1.0000000001", ++test_no);
	ok += test("1.00000000010000000000", ++test_no);

	ok += test("3.14", ++test_no);
	ok += test("3.141", ++test_no);
	ok += test("3.1415", ++test_no);
	ok += test("3.14159", ++test_no);
	ok += test("3.141592", ++test_no);
	ok += test("3.1415926", ++test_no);
	ok += test("3.14159265", ++test_no);
	ok += test("3.141592653", ++test_no);
	ok += test("3.1415926535", ++test_no);
	ok += test("3.14159265358", ++test_no);
	ok += test("3.141592653589", ++test_no);
	ok += test("3.1415926535897", ++test_no);
	ok += test("3.14159265358979", ++test_no);
	ok += test("3.141592653589793", ++test_no);
	ok += test("3.1415926535897932", ++test_no);
	ok += test("3.14159265358979323", ++test_no);
	ok += test("3.141592653589793238", ++test_no);
	ok += test("3.1415926535897932384", ++test_no);
	ok += test("3.14159265358979323846", ++test_no);
	ok += test("3.141592653589793238462", ++test_no);
	ok += test("3.1415926535897932384626", ++test_no);
	ok += test("3.14159265358979323846264", ++test_no);
	ok += test("3.141592653589793238462643", ++test_no);
	ok += test("3.1415926535897932384626433", ++test_no);
	ok += test("3.14159265358979323846264338", ++test_no);
	ok += test("3.141592653589793238462643383", ++test_no);
	ok += test("3.1415926535897932384626433832", ++test_no);
	ok += test("3.14159265358979323846264338327", ++test_no);
	ok += test("3.141592653589793238462643383279", ++test_no);
	ok += test("3.1415926535897932384626433832795", ++test_no);
	ok += test("3.14159265358979323846264338327950", ++test_no);
	ok += test("3.141592653589793238462643383279502", ++test_no);
	ok += test("3.1415926535897932384626433832795028", ++test_no);
	ok += test("3.14159265358979323846264338327950288", ++test_no);
	ok += test("3.141592653589793238462643383279502884", ++test_no);
	ok += test("3.1415926535897932384626433832795028841", ++test_no);
	ok += test("3.14159265358979323846264338327950288419", ++test_no);
	ok += test("3.141592653589793238462643383279502884197", ++test_no);
	ok += test("3.1415926535897932384626433832795028841971", ++test_no);
	ok += test("3.14159265358979323846264338327950288419716", ++test_no);
	ok += test("3.141592653589793238462643383279502884197169", ++test_no);
	ok += test("3.1415926535897932384626433832795028841971693", ++test_no);
	ok += test("3.14159265358979323846264338327950288419716939", ++test_no);
	ok += test("3.141592653589793238462643383279502884197169399", ++test_no);
	ok += test("3.1415926535897932384626433832795028841971693993", ++test_no);
	ok += test("3.14159265358979323846264338327950288419716939937", ++test_no);
	ok += test("3.141592653589793238462643383279502884197169399375", ++test_no);
	ok += test(".1415", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);
	ok += test("", ++test_no);

	printf(" ## RESULT ##\n");
	printf("     OK: %d, NG: %d\n\n", ok, test_no - ok);
}
