/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:05 by abdali            #+#    #+#             */
/*   Updated: 2026/03/10 04:54:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Convert string to long long integer.
 * @param s Input string to convert.
 * @return Converted long long value. Returns 0 if input is invalid.
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
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}
