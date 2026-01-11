/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:04:52 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 20:38:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	str[10];
	int		i;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr == 0)
		return (ft_putchar_fd('0', fd));
	i = 0;
	while (nbr)
	{
		str[i++] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	i--;
	while (i >= 0)
		ft_putchar_fd(str[i--], fd);
}
