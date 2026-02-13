/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	obj_read_id(t_parser *p, char *id, size_t max_len)
{
	size_t	i;
	char	c;

	parser_skip_spaces(p);
	i = 0;
	c = parser_peek(p);
	if (!c || c == '\n')
		return (false);
	while (c && !ft_isspace(c) && i < max_len - 1)
	{
		id[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	id[i] = 0;
	return (i > 0);
}

void	obj_skip_line(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}
