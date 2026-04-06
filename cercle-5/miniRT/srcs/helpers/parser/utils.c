/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_skip_spaces(t_parser *p)
{
	char	c;
	int		count;

	count = 0;
	c = parser_peek(p);
	while (c)
	{
		if (ft_isspace(c))
		{
			parser_advance(p);
			c = parser_peek(p);
			count++;
			if (count > 1000000)
			{
				ft_print_debug("CRITICAL ERROR: parser_skip_spaces loop\n");
				fflush(stdout);
				break ;
			}
		}
		else
			break ;
	}
}

void	parser_skip_horizontal_spaces(t_parser *p)
{
	char	c;

	c = parser_peek(p);
	while (c == ' ' || c == '\t' || c == '\v' || c == '\f')
	{
		parser_advance(p);
		c = parser_peek(p);
	}
}

bool	parser_match(t_parser *p, char expected)
{
	parser_skip_spaces(p);
	if (parser_peek(p) == expected)
	{
		parser_advance(p);
		return (true);
	}
	return (false);
}

bool	parser_get_line(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	i = 0;
	c = parser_peek(p);
	if (!c && p->eof)
		return (false);
	while (c && c != '\n' && c != '\r' && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	if (c == '\r')
	{
		parser_advance(p);
		c = parser_peek(p);
	}
	if (c == '\n')
		parser_advance(p);
	buf[i] = '\0';
	return (true);
}
