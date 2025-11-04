/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/24 11:41:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

static int	ft_handle_format(va_list args, char format)
{
	if (format == 'c')
		return (ft_handle_char(args));
	else if (format == 's')
		return (ft_handle_string(args));
	else if (format == 'p')
		return (ft_handle_pointer(args));
	else if (format == 'd' || format == 'i' || format == 'u')
		return (ft_handle_number(args, format));
	else if (format == 'x' || format == 'X')
		return (ft_handle_hex(args, format));
	else if (format == '%')
		return (ft_handle_percent());
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_handle_format(args, format[i]);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
