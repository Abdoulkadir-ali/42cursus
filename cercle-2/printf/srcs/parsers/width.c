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

static void	parse_width_star(size_t *i, va_list args, t_flags *flags)
{
	long	width;

	width = (long)va_arg(args, int);
	(*i)++;
	if (width < 0)
	{
		width = -width;
		flags->minus = 1;
		flags->zero = 0;
	}
	flags->width = (size_t)width;
}

static void	parse_width_digits(const char *str, size_t *i, t_flags *flags)
{
	int	wid;

	wid = ft_atoi(str, i);
	if (wid < 0)
		flags->width = 0;
	else
		flags->width = (size_t)wid;
}

void	ft_parse_width(const char *str, size_t *i, va_list args, t_flags *flags)
{
	char	c;

	c = str[*i];
	flags->width = 0;
	if (c == '*')
		parse_width_star(i, args, flags);
	else if (ft_isdigit(c))
		parse_width_digits(str, i, flags);
}
