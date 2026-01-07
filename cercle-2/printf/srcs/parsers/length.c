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

static void	parse_l(const char *str, size_t *i, t_flags *flags)
{
	if (str[*i + 1] == 'l')
	{
		flags->length = LEN_LL;
		(*i) += 2;
	}
	else
	{
		flags->length = LEN_L;
		(*i)++;
	}
}

static void	parse_h(const char *str, size_t *i, t_flags *flags)
{
	if (str[*i + 1] == 'h')
	{
		flags->length = LEN_HH;
		(*i) += 2;
	}
	else
	{
		flags->length = LEN_H;
		(*i)++;
	}
}

void	ft_parse_length(const char *str, size_t *i, t_flags *flags)
{
	char	c;

	c = str[*i];
	if (c == 'l')
		parse_l(str, i, flags);
	else if (c == 'h')
		parse_h(str, i, flags);
}
