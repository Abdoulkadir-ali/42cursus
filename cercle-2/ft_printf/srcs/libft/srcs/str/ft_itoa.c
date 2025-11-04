/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:51 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 20:38:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
