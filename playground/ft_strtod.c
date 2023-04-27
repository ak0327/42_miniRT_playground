/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 14:53:08 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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





static int get_num_part(const char *str, double *num, double *sign, size_t *idx, long *exp)
{
	size_t 	i;
	int 	digit;

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
	while ('0' <= str[*idx] && str[*idx] <= '9')
	{
		digit = str[*idx] - '0';
		if (*num * 10 + digit >= *num)
			*num = *num * 10 + str[*idx] - '0';
		else
			*exp += 1;
		*idx += 1;
	}
	if (str[*idx] == '.')
	{
		*idx += 1;
		while ('0' <= str[*idx] && str[*idx] <= '9')
		{
			digit = str[*idx] - '0';
			if (*num * 10 + digit >= *num)
				*num = *num * 10 + digit;
			else
				*exp += 1;
			*exp -= 1;
			*idx += 1;
		}
	}
	return (SUCCESS);
}

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
	if (num == of_div && digit > of_mod)
		return (false);
	return (true);
}

static int	get_exp_part(const char *str, double *num, size_t *idx, long *e)
{
	double 	negative;
	size_t 	i;
	long 	exp;
	int 	digit;

	exp = 0;
	negative = false;
	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
		return (SUCCESS);
	i = 1;
	if (!str[*idx + i])
		return (FAILURE);
	if (str[*idx + 1] == '-')
		negative = true;
	if (str[*idx + i] == '-' || str[*idx + i] == '+')
		i++;
	if (!str[*idx + i] || !isdigit(str[*idx + i]))
		return (FAILURE);
	while ('0' <= str[*idx + i] && str[*idx + i] <= '9')
	{
		digit = str[*idx + i] - '0';
		if (is_under_long(exp, digit, negative))
			exp = exp * 10 + digit;
		else
		{
			if (negative)
				exp = LONG_MIN;
			else
				exp = LONG_MAX;
			break ;
		}
		i++;
	}
	if (exp != LONG_MIN && negative)
		exp = -exp;

	if ((exp >= 0 && *e <= 0) || (exp <= 0 && *e >= 0))
		*e += exp;
	else if (exp >= 0 && *e >= 0)
	{
		if (LONG_MAX - exp >= *e)
			*e += exp;
		else
			*e = LONG_MAX;
	}
	else
	{
		if (exp - LONG_MIN >= -*e)
			*e += exp;
		else
			*e = LONG_MIN;
	}

	*num *= pow(10, *e);
	*idx += i;
	return (SUCCESS);
}

//static int	get_exp_part(const char *str, double *num, size_t *idx, long *e)
//{
//	double 	negative;
//	size_t 	i;
//	long 	exp;
//	int 	digit;
//
//	exp = 0;
//	negative = false;
//	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
//		return (SUCCESS);
//	i = 1;
//	if (!str[*idx + i])
//		return (FAILURE);
//	if (str[*idx + 1] == '-')
//		negative = true;
//	if (str[*idx + i] == '-' || str[*idx + i] == '+')
//		i++;
//	if (!str[*idx + i] || !isdigit(str[*idx + i]))
//		return (FAILURE);
//	while ('0' <= str[*idx + i] && str[*idx + i] <= '9')
//	{
//		digit = str[*idx + i] - '0';
//		if (is_under_long(exp, digit, negative))
//			exp = exp * 10 + digit;
//		else
//		{
//			if (negative)
//				exp = LONG_MIN;
//			else
//				exp = LONG_MAX;
//			break ;
//		}
//		i++;
//	}
//	if (exp != LONG_MIN && negative)
//		exp = -exp;
//	if ((exp >= 0 && *e <= 0) || (exp <= 0 && *e >= 0))
//		*e += exp;
//	else if (exp >= 0 && *e >= 0)
//	{
//		if (LONG_MAX - exp >= *e)
//			*e += exp;
//		else
//			*e = LONG_MAX;
//	}
//	else
//	{
//		if (exp - LONG_MIN >= -*e)
//			*e += exp;
//		else
//			*e = LONG_MIN;
//	}
//
//	*num *= pow(10, exp);
//	*idx += i;
//	return (SUCCESS);
//}

double	ft_strtod(const char *str, char **err)
{
	double	num;
	double 	num_sign;
	long 	exp;
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
	if (get_num_part(str, &num, &num_sign, &idx, &exp) == FAILURE)
	{
		*err = (char *)&str[idx];
		return (num);
	}
	if (get_exp_part(str, &num, &idx, &exp) == FAILURE)
	{
		*err = (char *)&str[idx];
		return (num_sign * num);
	}
	*err = (char *)&str[idx];
	return (num_sign * num);
}







//
//static int get_num_part(const char *str, uint64_t *n, double *sign, size_t *idx, long *exp)
//{
//	size_t 		i;
//	int 		digit;
//
//	*n = 0;
//	*exp = 0;
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
//	while (isdigit(str[*idx]))
//	{
//		digit = str[*idx] - '0';
//		if (*n <= SIZE_MAX / 10)
//			*n = *n * 10 + digit;
//		else
//			*exp += 1;
//		*idx += 1;
//	}
////	printf("[get_num_part-1] n:%llo, exp:%ld\n", *n, *exp);
//	if (str[*idx] == '.')
//	{
//		*idx += 1;
//		while (isdigit(str[*idx]))
//		{
//			if (*n <= DBL_MAX / 10)
//				*n = *n * 10 + str[*idx] - '0';
//			else
//				*exp += 1;
//			*exp -= 1;
//			*idx += 1;
//		}
//	}
////	printf("[get_num_part-2] n:%llo, exp:%ld\n", *n, *exp);
//	return (SUCCESS);
//}
//
//static int	get_exp_part(const char *str, size_t *idx, long *exp)
//{
//	bool	exp_negative;
//	long 	exp_val;
//	size_t 	i;
//
//	exp_negative = false;
//	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
//		return (SUCCESS);
//	i = 1;
//	if (!str[*idx + i])
//		return (FAILURE);
//	if (str[*idx + 1] == '-')
//		exp_negative = true;
//	if (str[*idx + i] == '-' || str[*idx + i] == '+')
//		i++;
//	if (!str[*idx + i] || !isdigit(str[*idx + i]))
//		return (FAILURE);
//	while ('0' <= str[*idx + i] && str[*idx + i] <= '9')
//	{
//		if (exp_negative && exp_val < LONG_MIN / 10)
//		{
//			exp_val = LONG_MIN;
//			break ;
//		}
//		else if (!exp_negative && exp_val > LONG_MAX / 10)
//		{
//			exp_val = LONG_MAX;
//			break ;
//		}
//		if (exp_negative)
//			exp_val = exp_val * 10 - (str[*idx + i] - '0');
//		else
//			exp_val = exp_val * 10 + (str[*idx + i] - '0');
//		i++;
//	}
//	*exp = *exp + exp_val;
////	printf("[get_exp_part] exp:%ld, exp_val:%ld\n", *exp, exp_val);
//	*idx += i;
//	return (SUCCESS);
//}
//
//double	get_double_fpn(uint64_t n, long exp)
//{
//	double	num;
//
//	num = n * pow(10, exp);
//
////	printf("[get_fpn]n:%lld, exp:%ld, num:%f\n", n, exp, num);
//	return (num);
//}
//
//double	ft_strtod(const char *str, char **endptr)
//{
//	uint64_t	n;
//	long 		exp;
//
//	double	num;
//	double 	num_sign;
//	size_t	idx;
//
//	idx = 0;
//	num = 0.0;
//	num_sign = 1.0;
//	exp = 0;
//	if (!str)
//	{
//		*endptr = (char *)&str[idx];
//		return (num);
//	}
//	if (get_num_part(str, &n, &num_sign, &idx, &exp) == FAILURE)
//	{
//		*endptr = (char *)&str[idx];
//		return (num);
//	}
//	if (get_exp_part(str,&idx, &exp) == FAILURE)
//	{
//		*endptr = (char *)&str[idx];
//		return (num_sign * num);
//	}
//
//	num = get_double_fpn(n, exp);
//
//	*endptr = (char *)&str[idx];
//	return (num_sign * num);
//}
//
