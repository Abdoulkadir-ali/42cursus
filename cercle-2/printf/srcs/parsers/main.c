/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:49:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/29 19:49:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_flags(const char *str, size_t *i, t_flags *flags)
{
	char	c;

	c = str[*i];
	while (ft_strchr("-0# +", c))
	{
		if (c == '-')
			flags->minus = 1;
		else if (c == '0')
			flags->zero = 1;
		else if (c == '#')
			flags->hash = 1;
		else if (c == '+')
			flags->plus = 1;
		else if (c == ' ')
			flags->space = 1;
		(*i)++;
		c = str[*i];
	}
	if (flags->minus)
		flags->zero = 0;
	if (flags->plus)
		flags->space = 0;
}

t_flags	ft_build_flags(const char *str, size_t *i, va_list args)
{
	t_flags	flags;

	flags = (t_flags){0};
	ft_parse_flags(str, i, &flags);
	ft_parse_width(str, i, args, &flags);
	ft_parse_precision(str, i, args, &flags);
	ft_parse_length(str, i, &flags);
	return (flags);
}
