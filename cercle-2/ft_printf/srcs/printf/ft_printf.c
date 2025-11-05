/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 19:47:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->has_precision = 0;
	flags->type = 0;
}

static int	ft_handle_percent(t_flags *flags)
{
	(void)flags;
	ft_putchar_fd('%', 1);
	return (1);
}

static int	ft_handle_format(va_list args, t_flags *flags)
{
	if (flags->type == 'c')
		return (ft_handle_char(args, flags));
	else if (flags->type == 's')
		return (ft_handle_string(args, flags));
	else if (flags->type == 'p')
		return (ft_handle_pointer(args, flags));
	else if (flags->type == 'd' || flags->type == 'i')
		return (ft_handle_number(args, flags));
	else if (flags->type == 'u')
		return (ft_handle_number(args, flags));
	else if (flags->type == 'x' || flags->type == 'X')
		return (ft_handle_hex(args, flags));
	else if (flags->type == '%')
		return (ft_handle_percent(flags));
	return (0);
}

static int	ft_process_format(const char *format, int *i, va_list args,
	int *count)
{
	t_flags	flags;

	(*i)++;
	ft_init_flags(&flags);
	ft_parse_flags(format, i, &flags);
	*count += ft_handle_format(args, &flags);
	(*i)++;
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
			ft_process_format(format, &i, args, &count);
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
			i++;
		}
	}
	va_end(args);
	return (count);
}
