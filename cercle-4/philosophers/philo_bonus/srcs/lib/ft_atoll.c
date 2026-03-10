/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:05 by abdali            #+#    #+#             */
/*   Updated: 2026/03/10 05:05:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * ft_atoll - Converts a string to a long long integer.
 * @s: Input string to convert.
 *
 * Handles optional whitespace, sign, and digit parsing.
 * Returns the converted value, or 0 if invalid.
 */
long long	ft_atoll(const char *s)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	return (res * sign);
}
