/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 03:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:21:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_peek_char(t_parser *parser, char *out)
{
	if (!parser || parser->pos >= parser->len)
	{
		parser->eof = true;
		return (0);
	}
	if (out)
		*out = parser->full_content[parser->pos];
	return (1);
}

int	parser_next_char(t_parser *parser, char *out)
{
	if (!parser_peek_char(parser, out))
		return (0);
	parser->pos++;
	return (1);
}

void	parser_skip_whitespace(t_parser *parser)
{
	char	c;

	while (parser_peek_char(parser, &c) && ft_isspace((unsigned char)c))
		parser_next_char(parser, NULL);
}

int	parser_is_eof(t_parser *parser)
{
	if (!parser)
		return (1);
	return (parser->pos >= parser->len);
}
