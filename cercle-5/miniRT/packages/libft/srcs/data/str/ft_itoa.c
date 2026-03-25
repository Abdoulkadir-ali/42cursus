/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:51 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:10:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Executes public ft_numlen utility.
 * @note Public library exported function.
 */
int	ft_numlen(long *num)
{
	long	temp;
	int		i;

	i = 0;
	if (!*num)
		return (1);
	if (*num < 0)
	{
		i++;
		*num = -*num;
	}
	temp = *num;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	return (i);
}

/**
 * @brief Allocates and returns a string representing 
 * the integer received as an argument.
 * @note Public library exported function.
 */
char	*ft_itoa(int n)
{
	long	num;
	int		i;
	char	*str;

	if (!n)
		return (ft_strdup("0"));
	num = n;
	i = ft_numlen(&num);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
