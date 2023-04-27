/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:56:00 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 15:35:46 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main(void)
{
	printf("LONG_MAX   : % ld\n", LONG_MAX);
	printf("LONG_MAX/10: % ld\n", LONG_MAX / 10);
	printf("LONG_MAX%%10: % ld\n", LONG_MAX % 10);
	printf("\n");
	printf("LONG_MIN   : % ld\n", LONG_MIN);
	printf("LONG_MIN/10: % ld\n", LONG_MIN / 10);
	printf("LONG_MIN%%10: % ld\n", LONG_MIN % 10);
	printf("\n");
	printf("-(LONG_MIN/10): % ld\n", -(LONG_MIN / 10));
	printf("-LONG_MIN/10  : % ld\n", -LONG_MIN / 10);

	printf("-(LONG_MIN%%10): % ld\n", -(LONG_MIN % 10));
	printf("-LONG_MIN%%10  : % ld\n", -LONG_MIN % 10);


	return (0);
}

/*

LONG_MAX   : 9223372036854775807
LONG_MAX/10: 922337203685477580
LONG_MAX%10: 7

LONG_MIN   : -9223372036854775808
LONG_MIN/10: -922337203685477580
LONG_MIN%10: -8

-(LONG_MIN/10):  922337203685477580
-LONG_MIN/10  : -922337203685477580
-(LONG_MIN%10):  8
-LONG_MIN%10  : -8

 */
