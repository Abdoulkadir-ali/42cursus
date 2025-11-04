/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/24 11:40:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_value_in_base(char c, const char *base)
{
	int	i;

	if (!base)
		return (-1);
	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

long long int	ft_atoi_base(const char *str, const char *base)
{
	long long int result;
	int sign;
	int digit;
	int base_len;

	if (!ft_check_base(base) || !str)
		return (0);
	result = 0;
	sign = 1;
	base_len = ft_strlen(base);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		digit = ft_get_value_in_base(*str, base);
		if (digit == -1)
			break ;
		result = result * base_len + digit;
		str++;
	}
	return (result * sign);
}