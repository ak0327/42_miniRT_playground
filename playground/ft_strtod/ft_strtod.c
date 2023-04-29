/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:24:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 16:16:56 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod.h"

static void	init_parse_info(t_parse_info *p)
{
	p->negative = false;
	p->exponent = 0;
	p->mantissa = 0;
	p->int_digit = 0;
}

double	ft_strtod(const char *str, char **endptr)
{
	t_parse_info	parse_info;
	char			*end;
	int 			parse_result;
	double 			dn;

	init_parse_info(&parse_info);
	parse_result = parse_float_str(str, &parse_info, &end);
	dn = convert_to_double(parse_info, parse_result);

	if (endptr)
		*endptr = end;
	return (dn);
}





