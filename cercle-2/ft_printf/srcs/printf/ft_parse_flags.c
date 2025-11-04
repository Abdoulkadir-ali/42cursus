/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 10:51:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_normalize_flags(t_flags *flags)
{
	if (flags->minus)
		flags->zero = 0;
	if (flags->plus)
		flags->space = 0;
	if (flags->has_precision)
		flags->zero = 0;
	if (flags->type == 'c' || flags->type == 's' || flags->type == 'p'
		|| flags->type == '%')
	{
		flags->zero = 0;
		flags->plus = 0;
		flags->space = 0;
	}
	if (flags->type != 'x' && flags->type != 'X')
		flags->hash = 0;
}

static void	ft_parse_flag_chars(const char *format, int *i, t_flags *flags)
{
	while (format[*i] == '-' || format[*i] == '0' || format[*i] == '#'
		|| format[*i] == ' ' || format[*i] == '+')
	{
		if (format[*i] == '-')
			flags->minus = 1;
		else if (format[*i] == '0')
			flags->zero = 1;
		else if (format[*i] == '#')
			flags->hash = 1;
		else if (format[*i] == ' ')
			flags->space = 1;
		else if (format[*i] == '+')
			flags->plus = 1;
		(*i)++;
	}
}

int	ft_parse_flags(const char *format, int *i, t_flags *flags)
{
	ft_parse_flag_chars(format, i, flags);
	while (format[*i] >= '0' && format[*i] <= '9')
		flags->width = flags->width * 10 + (format[(*i)++] - '0');
	if (format[*i] == '.')
	{
		flags->has_precision = 1;
		(*i)++;
		while (format[*i] >= '0' && format[*i] <= '9')
			flags->precision = flags->precision * 10 + (format[(*i)++] - '0');
	}
	flags->type = format[*i];
	ft_normalize_flags(flags);
	return (0);
}
