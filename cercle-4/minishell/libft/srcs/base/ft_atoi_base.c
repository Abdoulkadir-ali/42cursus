/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 11:01:25 by abdoali          ###   ########.fr       */
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

static void	ft_skip_whitespace_and_sign(const char **str, int *sign)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	while (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}

long long int	ft_atoi_base(const char *str, const char *base)
{
	long long int	result;
	int				sign;
	int				digit;

	if (!ft_check_base(base) || !str)
		return (0);
	result = 0;
	sign = 1;
	ft_skip_whitespace_and_sign(&str, &sign);
	while (*str)
	{
		digit = ft_get_value_in_base(*str++, base);
		if (digit == -1)
			break ;
		result = result * ft_strlen(base) + digit;
	}
	return (result * sign);
}
