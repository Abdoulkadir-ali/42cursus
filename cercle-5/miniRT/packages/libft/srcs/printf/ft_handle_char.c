/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 13:14:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handle_char(va_list args, t_flags *flags)
{
	char	c;
	int		count;

	c = (char)va_arg(args, int);
	count = 0;
	if (flags->minus)
	{
		ft_putchar_fd(c, flags->fd);
		count = 1 + ft_print_width(flags->width - 1, 0, 0, flags->fd);
	}
	else
	{
		count = ft_print_width(flags->width - 1, 0, 0, flags->fd);
		ft_putchar_fd(c, flags->fd);
		count++;
	}
	return (count);
}
