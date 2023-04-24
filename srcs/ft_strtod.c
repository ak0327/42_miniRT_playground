/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:38:53 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 18:53:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// NG : --0.0
//    :    .123
//    :   1..23
//    :   1.23-
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
	while (ft_isspace(str[idx]))
		idx++;
	if (str[idx] == '-')
		sign = -1;
	if (str[idx] == '-' || str[idx] == '+')
		idx++;
	if (!ft_isdigit(str[idx]))
		return (0);
	while (ft_isdigit(str[idx]))
	{
		ret_num = ret_num * 10 + str[idx] - '0';
		idx++;
	}
	if (str[idx] == '.')
		idx++;
	scale = 10.0;
	while (ft_isdigit(str[idx]))
	{
		ret_num += (double)(str[idx] - '0') / scale;
		scale *= 10.0;
		idx++;
	}
	if (!str[idx])
		*is_success = true;
	return (sign * ret_num);
}
