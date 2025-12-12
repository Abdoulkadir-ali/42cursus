/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:18:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 20:33:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	while (is_space(**str))
		(*str)++;
	while (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -sign;
		(*str)++;
	}
	return (sign);
}

static long	parse_digits(const char **str, int *error)
{
	long	res;
	int		digit;

	res = 0;
	if (!ft_isdigit(**str))
	{
		*error = 1;
		return (0);
	}
	while (ft_isdigit(**str))
	{
		digit = **str - '0';
		if (res > (LONG_MAX - digit) / 10)
		{
			*error = 1;
			return (0);
		}
		res = res * 10 + digit;
		(*str)++;
	}
	return (res);
}

long	parse_int(const char *str, int *error)
{
	int		sign;
	long	res;

	*error = 0;
	sign = parse_sign(&str);
	res = parse_digits(&str, error);
	if (*error)
		return (0);
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
	{
		*error = 1;
		return (0);
	}
	return (res);
}
