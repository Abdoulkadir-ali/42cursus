/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:23:08 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/29 20:23:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_precision_star(size_t *i, va_list args, t_flags *flags)
{
	int	prec;

	prec = va_arg(args, int);
	(*i)++;
	if (prec < 0)
	{
		flags->dot = 0;
		flags->precision = 0;
	}
	else
		flags->precision = (size_t)prec;
}

static void	parse_precision_digits(const char *str, size_t *i, t_flags *flags)
{
	int	prec;

	prec = ft_atoi(str, i);
	if (prec < 0)
		flags->precision = 0;
	else
		flags->precision = (size_t)prec;
}

void	ft_parse_precision(const char *str, size_t *i, va_list args,
		t_flags *flags)
{
	char	c;

	c = str[*i];
	if (c == '.')
	{
		flags->dot = 1;
		(*i)++;
		flags->precision = 0;
		c = str[*i];
		if (c == '*')
			parse_precision_star(i, args, flags);
		else if (ft_isdigit(c))
			parse_precision_digits(str, i, flags);
	}
}
