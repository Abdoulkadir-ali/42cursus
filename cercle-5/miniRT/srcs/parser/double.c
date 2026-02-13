/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_sign(t_parser *p)
{
	int		sign;
	char	c;

	sign = 1;
	c = parser_peek(p);
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		parser_advance(p);
	}
	return (sign);
}

static double	parse_integer_part(t_parser *p)
{
	double	result;
	char	c;

	result = 0.0;
	c = parser_peek(p);
	while (c >= '0' && c <= '9')
	{
		result = result * 10.0 + (c - '0');
		parser_advance(p);
		c = parser_peek(p);
	}
	return (result);
}

static double	parse_fraction_part(t_parser *p)
{
	double	result;
	double	divisor;
	char	c;

	if (parser_peek(p) != '.')
		return (0.0);
	parser_advance(p);
	divisor = 10.0;
	result = 0.0;
	c = parser_peek(p);
	while (c >= '0' && c <= '9')
	{
		result += (c - '0') / divisor;
		divisor *= 10.0;
		parser_advance(p);
		c = parser_peek(p);
	}
	return (result);
}

double	parse_double(t_parser *p)
{
	double	result;
	int		sign;

	parser_skip_spaces(p);
	sign = parse_sign(p);
	result = parse_integer_part(p);
	result += parse_fraction_part(p);
	return (result * sign);
}
