/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:22:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:22:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	trim_path_buf(char *buf, size_t *i)
{
	while (*i > 0 && (buf[*i - 1] == ' ' || buf[*i - 1] == '\t'))
		(*i)--;
	buf[*i] = '\0';
}

bool	parse_path_safe(t_parser *p, char *buf, size_t size)
{
	size_t	i;
	char	c;
	bool	quoted;

	parser_skip_horizontal_spaces(p);
	i = 0;
	c = parser_peek(p);
	quoted = (c == '"');
	if (quoted)
		parser_advance(p);
	while (i < size - 1)
	{
		c = parser_peek(p);
		if (!c || (quoted && c == '"')
			|| (!quoted && (c == '\n' || c == '\r' || c == '#')))
			break ;
		buf[i++] = c;
		parser_advance(p);
	}
	if (quoted && parser_peek(p) == '"')
		parser_advance(p);
	trim_path_buf(buf, &i);
	return (i > 0);
}
