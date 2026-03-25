/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:56:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Normalizes the flags based on type and other flags.
 * @note Public library exported function.
 */
static void	ft_normalize_flags(t_flags *flags)
{
	if (flags->minus)
		flags->zero = false;
	if (flags->plus)
		flags->space = false;
	if (flags->has_precision)
		flags->zero = false;
	if (flags->type == 'c' || flags->type == 's' || flags->type == 'p'
		|| flags->type == '%')
	{
		flags->zero = false;
		flags->plus = false;
		flags->space = false;
	}
	if (flags->type != 'x' && flags->type != 'X')
		flags->hash = false;
}

static void	ft_parse_flag_chars(const char *format, int *i, t_flags *flags)
{
	while (format[*i] == '-' || format[*i] == '0' || format[*i] == '#'
		|| format[*i] == ' ' || format[*i] == '+')
	{
		if (format[*i] == '-')
			flags->minus = true;
		else if (format[*i] == '0')
			flags->zero = true;
		else if (format[*i] == '#')
			flags->hash = true;
		else if (format[*i] == ' ')
			flags->space = true;
		else if (format[*i] == '+')
			flags->plus = true;
		(*i)++;
	}
}

/**
 * @brief Executes public ft_parse_flags utility.
 * @note Public library exported function.
 */
int	ft_parse_flags(const char *format, int *i, t_flags *flags)
{
	ft_parse_flag_chars(format, i, flags);
	while (format[*i] >= '0' && format[*i] <= '9')
		flags->width = flags->width * 10 + (format[(*i)++] - '0');
	if (format[*i] == '.')
	{
		flags->has_precision = true;
		(*i)++;
		while (format[*i] >= '0' && format[*i] <= '9')
			flags->precision = flags->precision * 10 + (format[(*i)++] - '0');
	}
	flags->type = format[*i];
	ft_normalize_flags(flags);
	return (0);
}
