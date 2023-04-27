/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:12:48 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 12:51:38 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
//	printf("[get_num_part-1] n:%llo, exp:%ld\n", *n, *exp);
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
//	printf("[get_num_part-2] n:%llo, exp:%ld\n", *n, *exp);
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
//	printf("[get_exp_part] exp:%ld, exp_val:%ld\n", *exp, exp_val);
	*idx += i;
	return (SUCCESS);
}

double	get_double_fpn(uint64_t n, long exp)
{
	double	num;

	num = n * pow(10, exp);

//	printf("[get_fpn]n:%lld, exp:%ld, num:%f\n", n, exp, num);
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

