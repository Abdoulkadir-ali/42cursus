/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/01/08 07:05:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/08 07:05:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static long long	parse_digits(const char *str, size_t *i, int *error, int sign)
{
	long long	result;

	result = 0;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10 + (str[*i] - '0');
		(*i)++;
		if ((sign == 1 && result > INT_MAX) || (sign == -1 &&
				-result < INT_MIN))
		{
			*error = 1;
			return (0);
		}
	}
	return (result);
}

int	ft_atoi(const char *str, size_t *i, int *error)
{
	long long	result;
	int			sign;

	sign = 1;
	*error = 0;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	result = parse_digits(str, i, error, sign);
	return ((int)(result * sign));
}
