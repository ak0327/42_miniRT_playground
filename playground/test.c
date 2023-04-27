/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:56:00 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 13:10:55 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

typedef union longlongdouble{
	long long llnum;
	double dnum;
}			longlongdouble;

int main(void)
{
	longlongdouble lldnum = {0};
	lldnum.dnum = 1.2345;
	printf("llnum:%lld, dnum:%f\n", lldnum.llnum, lldnum.dnum);

	printf("fnum:%016llx\n", lldnum.llnum);
	lldnum.llnum = lldnum.llnum >> 8;
	printf("fnum:%016llx\n", lldnum.llnum);
	lldnum.llnum &= 0xFFFFFFFF00000000;
	printf("fnum:%016llx\n", lldnum.llnum);
	return 0;
}
