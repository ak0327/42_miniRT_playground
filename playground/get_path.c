/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:11:53 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 21:26:41 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

size_t	min_size(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	cpy_len;
	size_t	start_idx;
	char	*ret_str;

	if (s == NULL)
		return (NULL);
	start_idx = (size_t)start;
	if (strlen(s) < start_idx + 1)
		cpy_len = 0;
	else
		cpy_len = min_size(strlen(s) - start_idx, len);
	ret_str = (char *)calloc(sizeof(char), cpy_len + 1);
	if (ret_str == NULL)
		return (NULL);
	memcpy(ret_str, &s[start_idx], cpy_len);
	return (ret_str);
}

void	skip_delimiter(const char *line, size_t *idx)
{
	while (line[*idx] && isspace(line[*idx]))
		*idx += 1;
	if (line[*idx] == ',')
		*idx += 1;
	while (line[*idx] && isspace(line[*idx]))
		*idx += 1;
}

char	*get_path(const char *line, size_t *idx)
{
	char	*path;
	size_t	len;

	while (line[*idx] && isspace(line[*idx]))
		*idx += 1;
	if (line[*idx] != '"')
		return (NULL);
	*idx += 1;
	len = 0;
	while (line[*idx + len] && line[*idx + len] != '"')
		len++;
	path = ft_substr(line, *idx, len);
	if (!path)
		return (NULL);
	*idx += len + 1;
	return (path);
}

void	test(const char *paths)
{
	char	*path1;
	char	*path2;
	size_t	idx;

	idx = 0;
	path1 = get_path(paths, &idx);
	skip_delimiter(paths, &idx);
	path2 = get_path(paths, &idx);
	printf("%-40s -> [%s][%s]\n", paths, path1, path2);
}

int main(void)
{
	const char paths1[] = "\"test1\", \"test2\"";
	const char paths2[] = "\" test1 \", \" test2 \"";
	const char paths3[] = "\"1\", \"2\"";
	const char paths4[] = "   \"test1\"     ,    \"test2\"     ";
	const char paths5[] = "\"\", \"test2\"";
	const char paths6[] = "\"test1\", \"\"";
	const char paths7[] = "\"\", \"\"";

	test(paths1);
	test(paths2);
	test(paths3);
	test(paths4);
	test(paths5);
	test(paths6);
	test(paths7);
	printf("\n");
}






















