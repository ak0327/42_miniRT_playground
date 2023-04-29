/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:51:29 by takira            #+#    #+#             */
/*   Updated: 2023/04/29 11:45:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#define	SIZE	1024

typedef struct s_bignum
{
	int		num[SIZE];
	bool	negative;
	size_t	len;
	size_t	max_len;

}	t_bignum;

