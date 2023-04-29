/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:00 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 19:03:15 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

static double	convert_float_bin_to_double(t_parse_info p)
{
	t_b2d	b2d;



	return (b2d.double_num);
}

double	convert_to_double_(t_parse_info p, int parse_result)
{
	double	ret;

	if (parse_result == PARSER_MINUS_ZERO)
		return (-0.0);
	if (parse_result == PARSER_PLUS_ZERO)
		return (+0.0);
	if (parse_result == PARSER_MINUS_INF)
		return (-INFINITY);
	if (parse_result == PARSER_PLUS_INF)
		return (INFINITY);

	ret = convert_float_bin_to_double(p);
	return (ret);
}