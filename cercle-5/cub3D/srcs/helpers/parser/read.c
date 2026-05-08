/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 03:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:21:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_read_token(t_parser *parser, char *out, size_t max_len)
{
	char	c;
	size_t	count;

	if (!parser || !out || max_len == 0)
		return (0);
	parser_skip_whitespace(parser);
	count = 0;
	while (parser_peek_char(parser, &c) && !ft_isspace((unsigned char)c))
	{
		if (count + 1 < max_len)
			out[count] = c;
		count++;
		parser_next_char(parser, NULL);
	}
	if (count >= max_len)
		count = max_len - 1;
	out[count] = '\0';
	return (count > 0);
}

static int	parse_digits(t_parser *parser, long *result)
{
	char	c;
	int		ok;

	ok = 0;
	while (parser_peek_char(parser, &c) && c >= '0' && c <= '9')
	{
		*result = *result * 10 + (c - '0');
		parser_next_char(parser, NULL);
		ok = 1;
	}
	return (ok);
}

int	parser_read_int(t_parser *parser, int *value)
{
	char	c;
	int		sign;
	long	result;

	if (!parser || !value)
		return (0);
	parser_skip_whitespace(parser);
	if (!parser_peek_char(parser, &c))
		return (0);
	sign = 1;
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		parser_next_char(parser, NULL);
	}
	result = 0;
	if (!parse_digits(parser, &result))
		return (0);
	*value = (int)(result * sign);
	return (1);
}

int	parser_read_line_alloc(t_parser *parser, char **out)
{
	size_t	s;
	size_t	len;

	if (!parser || !out || parser->pos >= parser->len)
		return (0);
	s = parser->pos;
	while (parser->pos < parser->len
		&& parser->full_content[parser->pos] != '\n')
		parser->pos++;
	len = parser->pos - s;
	*out = malloc(len + 1);
	if (!*out)
		return (0);
	ft_memcpy(*out, parser->full_content + s, len);
	(*out)[len] = '\0';
	if (parser->pos < parser->len && parser->full_content[parser->pos] == '\n')
		parser->pos++;
	return (1);
}
