/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 16:35:25 by takira           ###   ########.fr       */
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
	size_t	idx;
	double	ret_num;
	int 	sign;

	ret_num = 0;
	idx = 0;
	sign = 1;
	*is_success = false;

	if (!str)
		return (0);

	while (isspace(str[idx]))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	if (!isnumber(str[idx]))
		return (0);

	while (isnumber(str[idx]))
	{

	}

	return (ret_num);
}

int test(const char *str, int no)
{
	double	ft_ret, lib_ret;
	bool	ft_is_success;
	char	*lib_err = NULL;
	int		ng;

	ft_ret = ft_strtod(str, &ft_is_success);
	lib_ret = strtod(str, &lib_err);

	ng  = 0;
	if (ft_ret == lib_ret)
		ng = 1;

	printf("[%02d]  ft=%10lf, lib=%lf, ret=%s\n", no, ft_ret, lib_ret, ng ? "OK" : "WA");
	return (ng);
}

int main(void)
{
	int	ng;
	int test_no;

	printf("############ TEST ############\n");

	ng = 0;
	test_no = 1;
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);
	ng += test("", test_no++);

	printf(" ## RESULT ##\n");
	printf("     OK: %d, ng: %d\n\n", test_no - ng, ng);
}