/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 10:59:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int n, int fd)
{
	char	str[10];
	int		i;

	if (n == 0)
		return (ft_putchar_fd('0', fd));
	i = 0;
	while (n)
	{
		str[i++] = n % 10 + '0';
		n = n / 10;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar_fd(str[i--], fd);
	}
}
