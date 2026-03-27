/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:44:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	rt_parse_token(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	parser_skip_spaces(p);
	i = 0;
	c = parser_peek(p);
	if (!c)
		return (false);
	while (c && !ft_isspace(c) && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	buf[i] = '\0';
	return (i > 0);
}

void	rt_parse_scale_raw(t_parser *p, t_vec3 *scale)
{
	char	c;
	double	s;
	size_t	saved;
	t_vec3	v;

	parser_skip_spaces(p);
	c = parser_peek(p);
	if ((c < '0' || c > '9') && c != '-' && c != '.')
	{
		*scale = vec3(1, 1, 1);
		return ;
	}
	saved = p->cursor;
	if (parse_vec3(p, &v))
		*scale = v;
	else
	{
		p->cursor = saved;
		s = parse_double(p);
		*scale = vec3(s, s, s);
	}
}
