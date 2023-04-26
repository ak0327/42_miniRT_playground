/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_gnulib_strtod.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:21:46 by takira            #+#    #+#             */
/*   Updated: 2023/04/26 09:21:46 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
double	scale_radix_exp(double x, int radix, long int exponent)
{
	long int  e = exponent;

	if (radix == 2)
		return (0);
	double r = x;

	if (r != 0)
	{
		if (e < 0)
		{
			while (e++ != 0)
			{
				r /= radix;
				if (r == 0 && x != 0)
				{
					errno = ERANGE;
					break ;
				}
			}
		}
		else
		{
			while (e-- != 0)
			{
				if (r < -DBL_MAX / radix)
				{
					errno = ERANGE;
					return (-HUGE_VAL);
				}
				else if (DBL_MAX / radix < r)
				{
					errno = ERANGE;
					return (HUGE_VAL);
				}
				else
					r *= radix;
			}
		}
	}
	return (r);
}

double	parse_number(const char *str_ptr, int base, int radix, int radix_multiplier, char expchar, char **endptr)
{
	const char	*s = str_ptr;
	bool		got_dot = false;
	long		exponent = 0;
	double 		num = 0;
	int 		digit;

	while (true)
	{
		if (isdigit(*s))
			digit = *s - '0';
		else if (!got_dot && *s == '.')
		{
			got_dot = true;
			continue ;
		}
		else
			break ;

		if (num <= DBL_MAX / base)
			num = num * base + digit;
		else
			exponent += radix_multiplier;

		if (got_dot)
			exponent -= radix_multiplier;
		s++;
	}
	if (tolower(*s) == expchar && !isspace(s[1]))
	{
		char *end;
		long value = strtol(s+1, &end, 10);
		if (s + 1 != end)
		{
			s = end;
			exponent = (exponent < 0
						? (value < LONG_MIN - exponent ? LONG_MIN : exponent + value)
						: (LONG_MAX - exponent < value ? LONG_MAX : exponent + value));
		}
	}
	*endptr = (char *)s;
	return (scale_radix_exp(num, radix, exponent));

}

double ft_strtod(const char *str, bool *is_success, char **endptr)
{
	bool	negative = false;

	double		num;
	const char	*s = str;
	const char	*end;
	char 		*endbuf;

	while (isspace(*s))
		++s;

	negative = *s == '-';
	if (*s == '-' || *s == '+')
		++s;

	num = strtod(s, &endbuf);
	end = endbuf;

	if (isdigit(s[*s == '.']))
	{
		const char	*e = s + 1;
		while (e < end && tolower(*e) != 'e')
			e++;
		if (e < end && !isdigit(e[1 + (e[1] == '-' || e[1] == '+')]))
		{
			num = parse_number(s, 10, 10, 1, 'e', &endbuf);
			end = e;
		}
		s = end;
	}
	else if (tolower(*s) == 'i' && tolower(s[1] == 'n' && tolower(s[2] == 'f')))
	{
		s += 3;
		if (tolower(*s) == 'i' \
			&& tolower(s[1]) == 'n' \
			&& tolower(s[2]) == 'i' \
			&& tolower(s[3]) == 't' \
			&& tolower(s[4]) == 'y')
			s += 5;
		num = HUGE_VAL;
		errno = ERANGE;
	}
	else if (tolower(*s) == 'n' && tolower(s[1]) == 'a' && tolower(s[2]) == 'n')
	{
		s += 3;
		if (s != end)
			num = NAN;
	}
	else
	{
		errno = EINVAL;
		s = str;
	}

	if (endptr != NULL)
		*endptr = (char *)s;
	if (!num && negative)
		return (-0.0);

	return (negative ? -num : num);
}