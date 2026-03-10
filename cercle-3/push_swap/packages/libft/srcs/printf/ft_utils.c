/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 18:32:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_width(int width, int zero, int left)
{
	int		count;
	char	c;

	count = 0;
	c = ' ';
	if (zero && !left)
		c = '0';
	while (width > 0)
	{
		ft_putchar_fd(c, 1);
		width--;
		count++;
	}
	return (count);
}

int	ft_count_digits(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_count_hex_digits(unsigned long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}
