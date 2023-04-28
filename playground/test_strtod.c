/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/28 14:23:03 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

typedef union s_bin
{
	double		d;
	long long	ll;
}			t_bin;

void	print_float_bit(double double_num, char *str);
t_bin	calc_xor(double a, double b);
void	print_diff_bit(double a, double b, char *str);

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

	ft_ret = ft_strtod(str, &ft_end);

	errno = 0;
	lib_ret = strtod(str, &lib_end);
	if (errno == ERANGE)
		is_lib_of = true;

	lib_of = is_lib_of ? "OF" : "-";

	/* return value */
	test_ret = fabs(ft_ret - lib_ret) < epsilon ? true : false;
	if (ft_ret == INFINITY && lib_ret == INFINITY)
		test_ret = true;

	/* endptr */
	test_endptr = (strcmp(ft_end, lib_end) == 0) ? true : false;

	if (test_ret && test_endptr)
	{
		res_ok = true;
		color_start = "\x1b[32m";
	}

	printf("%s"
		   "[%03d:%s] input    =    %s\n"
		   "         ft_ret   = %%f[%f],     endptr[%s]\n"
		   "         lib_ret  = %%f[%f],     endptr[%s],     ERANGE:%s\n"
		   "         diff_ret = %%f[%f],     %%e[%e]"
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
	print_float_bit(ft_ret,  "   bit:ft   = ");
	print_float_bit(lib_ret, "   bit:lib  = ");
	print_diff_bit(ft_ret, lib_ret,        "   bif:diff = ");
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

	printf("\n\n############################################################################\n\n");

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

	// parse error
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
	ok += test("1e", ++test_no, &res_ret, &res_end);
	ok += test("1e-", ++test_no, &res_ret, &res_end);
	ok += test("1e+", ++test_no, &res_ret, &res_end);
	ok += test(".e-", ++test_no, &res_ret, &res_end);

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
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890E+10000", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	ok += test("1.0E+10", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+50", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+100", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+150", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+200", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+250", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+300", ++test_no, &res_ret, &res_end);
	printf("\n\n");

	// testcase from https://note.com/sukesan1984/n/ncd78a5d6251c
	ok += test("18014398509482008", ++test_no, &res_ret, &res_end);
	ok += test("18014398509482009", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.1", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.2", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.21", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.22", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.23", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.24", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.25", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.26", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.27", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.28", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.29", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.3", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.4", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.5", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.6", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.7", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.74", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.75", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.76", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.77", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.8", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.9", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685249", ++test_no, &res_ret, &res_end);

	ok += test("0.00000123456e-123", ++test_no, &res_ret, &res_end);
	ok += test("1.7976931348623157e308", ++test_no, &res_ret, &res_end);
	ok += test("1.7976931348623157e308", ++test_no, &res_ret, &res_end);
	ok += test("2.2250738585072014e-308", ++test_no, &res_ret, &res_end);
	ok += test("2.2250738585072001e-308", ++test_no, &res_ret, &res_end);
	ok += test("2.2250738585072008e-308", ++test_no, &res_ret, &res_end);
	ok += test("9.8813129168249308e-324", ++test_no, &res_ret, &res_end);
	ok += test("4.9406564584124654e-324", ++test_no, &res_ret, &res_end);
	ok += test("4.9406564584124655e-324", ++test_no, &res_ret, &res_end);


	// try to overflow exponent
	ok += test("1e-4294967296", ++test_no, &res_ret, &res_end);
	ok += test("1e+4294967296", ++test_no, &res_ret, &res_end);
	ok += test("1e-18446744073709551616", ++test_no, &res_ret, &res_end);
	ok += test("1e+18446744073709551616", ++test_no, &res_ret, &res_end);


	// zeros
	ok += test("0", ++test_no, &res_ret, &res_end);
	ok += test("0e0", ++test_no, &res_ret, &res_end);
	ok += test("-0e0", ++test_no, &res_ret, &res_end);
	ok += test("+0e0", ++test_no, &res_ret, &res_end);
	ok += test("0e-0", ++test_no, &res_ret, &res_end);
	ok += test("-0e-0", ++test_no, &res_ret, &res_end);
	ok += test("+0e-0", ++test_no, &res_ret, &res_end);
	ok += test("0e+0", ++test_no, &res_ret, &res_end);
	ok += test("-0e+0", ++test_no, &res_ret, &res_end);
	ok += test("+0e+0", ++test_no, &res_ret, &res_end);


	printf("\n\n");


	printf(" ## RESULT ##\n");
	printf("     OK: %d, NG: %d\n", ok, test_no - ok);
	printf("     retNG:%d, errNG:%d\n\n", test_no - res_ret, test_no - res_end);

	printf("\n############################################################################");
	printf("\n############################################################################");
	printf("\n############################################################################\n\n\n");

	printf("1.0e+50\n");
	printf("0.1 * pow(10.0, 51.0)  :%f\n", 0.1 * pow(10.0, 51.0));
	printf("1.0 * pow(10.0, 50.0)  :%f\n", 1.0 * pow(10.0, 50.0));
	printf("10.0 * pow(10.0, 49.0) :%f\n", 10.0 * pow(10.0, 49.0));
	printf("100.0 * pow(10.0, 48.0):%f\n", 100.0 * pow(10.0, 48.0));
	printf("strtod('1.0e+50')      :%f\n", strtod("1.0e+50", NULL));

	ok += test("1.0E+50", ++test_no, &res_ret, &res_end);

	printf("\n\n");

	// NGケース一部
	ok += test("123456789012345678901", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345", ++test_no, &res_ret, &res_end);
	ok += test("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.21", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.22", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.23", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.24", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.25", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.6", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.7", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.75", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.76", ++test_no, &res_ret, &res_end);
	ok += test("2251799813685248.77", ++test_no, &res_ret, &res_end);
	ok += test("100000000000000.0000000000000000000000000001", ++test_no, &res_ret, &res_end);


	printf("        100000000000000.0                             :%f\n", 100000000000000.0);
	printf("        100000000000000.0 * pow(10.0, 0.0)            :%f\n", 100000000000000.0 * pow(10.0, 0.0));
	printf("        1000000000000000.0 * pow(10.0, -1.0)          :%f\n", 1000000000000000.0 * pow(10.0, -1.0));
	printf("        10000000000000000.0 * pow(10.0, -2.0)         :%f\n", 10000000000000000.0 * pow(10.0, -2.0));
	printf("        100000000000000000.0 * pow(10.0, -3.0)        :%f\n", 100000000000000000.0 * pow(10.0, -3.0));
	printf("        1000000000000000000.0 * pow(10.0, -4.0)       :%f\n", 1000000000000000000.0 * pow(10.0, -4.0));
	printf("        10000000000000000000.0 * pow(10.0, -5.0)      :%f\n", 10000000000000000000.0 * pow(10.0, -5.0));
	printf("        100000000000000000000.0 * pow(10.0, -6.0)     :%f\n", 100000000000000000000.0 * pow(10.0, -6.0));
	printf("        1000000000000000000000.0 * pow(10.0, -7.0)    :%f\n", 1000000000000000000000.0 * pow(10.0, -7.0));
	printf("        10000000000000000000000.0 * pow(10.0, -8.0)   :%f\n", 10000000000000000000000.0 * pow(10.0, -8.0));
	printf("        100000000000000000000000.0 * pow(10.0, -9.0)  :%f\n", 100000000000000000000000.0 * pow(10.0, -9.0));
	printf("        1000000000000000000000000.0 * pow(10.0, -10.0):%f\n", 1000000000000000000000000.0 * pow(10.0, -10.0));
	printf("\n");
	printf("strtod('100000000000000.0')                           :%f\n", strtod("100000000000000.0", NULL));
	printf("strtod('10000000000000000000.0')                      :%f\n", strtod("10000000000000000000.0", NULL));
	printf("strtod('100000000000000000000.0')                     :%f\n", strtod("100000000000000000000.0", NULL));
	printf("strtod('1000000000000000000000.0')                    :%f\n", strtod("1000000000000000000000.0", NULL));

	return (0);
}

void	print_float_bit(double double_num, char *str)
{
	t_bin num;

	num.d = double_num;
//	printf("%s double:%f -> [", str, lld.d);
	printf("%s [", str);

	int shift = 63;
	while (shift >= 0)
	{
		printf("%lld", (num.ll >> shift) & 1);
		if (shift == 63 || shift == 52)
			printf(" ");
		shift--;
	}
	printf("]\n");
}

void	print_diff_bit(double a, double b, char *str)
{
	t_bin	diff = calc_xor(a, b);
	int 	cnt = 0;

	printf("%s [", str);

	int shift = 63;
	while (shift >= 0)
	{
		if ((diff.ll >> shift) & 1)
		{
			printf("^");
			cnt++;
		}
		else
			printf(" ");
		if (shift == 63 || shift == 52)
			printf(" ");
		shift--;
	}
	printf("]");
	if (cnt > 0)
		printf(" diff:%d", cnt);
	printf("\n");
}

t_bin	calc_xor(double a, double b)
{
	t_bin	num_a, num_b;

	num_a.d = a;
	num_b.d = b;
	num_a.ll ^= num_b.ll;
	return (num_a);
}

//2147483647
//4294967295
//9223372036854775807
//18446744073709551615
