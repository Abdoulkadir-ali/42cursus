/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_entry_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

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

void	rt_parse_scale(t_parser *p, t_parse_obj *obj)
{
	char	c;
	double	s;
	size_t	saved;
	t_vec3	v;

	parser_skip_spaces(p);
	c = parser_peek(p);
	if ((c < '0' || c > '9') && c != '-' && c != '.')
	{
		obj->data.mesh_info.transform.scale = vec3(1, 1, 1);
		return ;
	}
	saved = p->cursor;
	if (parse_vec3(p, &v))
		obj->data.mesh_info.transform.scale = v;
	else
	{
		p->cursor = saved;
		s = parse_double(p);
		obj->data.mesh_info.transform.scale = vec3(s, s, s);
	}
}
