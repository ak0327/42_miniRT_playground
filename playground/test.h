/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:28 by takira            #+#    #+#             */
/*   Updated: 2023/04/27 15:27:40 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <sys/errno.h>
#include <float.h>

#define SUCCESS	0
#define FAILURE	1


double	ft_strtod(const char *str, char **err);

#endif //TEST_H
