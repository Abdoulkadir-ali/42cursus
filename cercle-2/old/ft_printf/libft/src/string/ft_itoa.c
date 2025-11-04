/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:27:14 by abdali            #+#    #+#             */
/*   Updated: 2025/10/22 22:59:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_sizeinteger(int n)
{
	int		size;
	long	nbr;

	nbr = n;
	size = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		size++;
	}
	while (nbr >= 10)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;
	int		i;

	len = ft_sizeinteger(n);
	str = (char *)malloc(1 + len * sizeof(char));
	if (!str)
		return (NULL);
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	i = 1;
	str[len] = '\0';
	while (nbr >= 10)
	{
		str[len - i] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	str[len - i] = ((nbr % 10) + '0');
	return (str);
}
