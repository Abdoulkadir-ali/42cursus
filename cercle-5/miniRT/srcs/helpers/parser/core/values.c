/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_int(t_parser *p)
{
	long	result;
	int		sign;
	char	c;

	result = 0;
	sign = 1;
	parser_skip_spaces(p);
	c = parser_peek(p);
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		parser_advance(p);
	}
	c = parser_peek(p);
	while (c >= '0' && c <= '9')
	{
		result = result * 10 + (c - '0');
		parser_advance(p);
		c = parser_peek(p);
	}
	return ((int)(result * sign));
}

bool	parse_vec3(t_parser *p, t_vec3 *out)
{
	t_vec3	v;

	ft_memset(&v, 0, sizeof(t_vec3));
	v.x = parse_double(p);
	parser_skip_spaces(p);
	if (parser_peek(p) == ',')
		parser_advance(p);
	else
		return (false);
	v.y = parse_double(p);
	parser_skip_spaces(p);
	if (parser_peek(p) == ',')
		parser_advance(p);
	else
		return (false);
	v.z = parse_double(p);
	*out = v;
	return (true);
}

bool	parse_vec2(t_parser *p, t_vec2 *out)
{
	t_vec2	v;

	ft_memset(&v, 0, sizeof(t_vec2));
	v.x = parse_double(p);
	parser_skip_spaces(p);
	if (parser_peek(p) == ',')
		parser_advance(p);
	else
		return (false);
	v.y = parse_double(p);
	*out = v;
	return (true);
}
