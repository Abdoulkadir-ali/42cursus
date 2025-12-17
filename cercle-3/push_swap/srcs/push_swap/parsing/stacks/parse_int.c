/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:18:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/17 12:19:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	long	res;
	int		sign;
	int		sign_count;

	*error = 0;
	sign = 1;
	sign_count = 0;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		sign_count++;
		str++;
	}
	if (sign_count > 1)
	{
		if (MULTIPLE_SIGN_INVALID)
		{
			*error = 1;
			return (0);
		}
	}
	res = parse_digits(&str, error);
	if (*error)
		return (0);
	if (*str != '\0')
	{
		*error = 1;
		return (0);
	}
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
	{
		*error = 1;
		return (0);
	}
	return (res);
}
