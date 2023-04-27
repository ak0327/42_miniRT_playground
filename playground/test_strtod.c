/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 19:10:03 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
void	print_float_bit(double double_num, char *str);

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

	lib_of = is_lib_of ? "OF" : "";

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
	ok += test("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890E+10000", ++test_no, &res_ret, &res_end);

	ok += test("1.0E+10", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+50", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+100", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+150", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+200", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+250", ++test_no, &res_ret, &res_end);
	ok += test("1.0E+300", ++test_no, &res_ret, &res_end);


	printf(" ## RESULT ##\n");
	printf("     OK: %d, NG: %d\n", ok, test_no - ok);
	printf("     retNG:%d, errNG:%d\n\n", test_no - res_ret, test_no - res_end);



//	test("123456789012345678901", ++test_no, &res_ret, &res_end);

//	print_float_bit(2147483647.9999995, "2147483647.9999995");
//	print_float_bit(2147483647.9999996, "2147483647.9999996");
//	print_float_bit(2147483647.9999997, "2147483647.9999997");
//	print_float_bit(2147483647.9999998, "2147483647.9999998");
//	print_float_bit(2147483647.9999999, "2147483647.9999999");
//	print_float_bit(2147483648.0000000, "2147483648.0000000");
//	print_float_bit(2147483648.0,       "2147483648.0");
//
//	ok += test("123.45e-12", ++test_no, &res_ret, &res_end);




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






