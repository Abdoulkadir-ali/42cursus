/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "scene.h"

bool	read_id(t_parser *p, char *buf, size_t max_len)
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

static void	handle_unknown(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}

bool	rt_parse_entry(t_scene *scene, t_rt *rt)
{
	if (!read_id(rt->parser, rt->id, sizeof(rt->id)))
		return (false);
	rt->obj = dispatch_scan(rt->parser, rt->id);
	if (rt->obj.type == TYPE_NONE)
	{
		fprintf(stderr, "Warning: unknown keyword '%s' (line %d)\n",
			rt->id, rt->line_num);
		handle_unknown(rt->parser);
		rt->status = false;
		return (true);
	}
	if (rt->obj.type == TYPE_MAT_MOD)
	{
		apply_mat_mod_to_last(scene, rt, &rt->obj.data.mat_mod);
		return (true);
	}
	if (!process_object(scene, rt->obj))
		rt->status = false;
	else
	{
		rt->last_type = rt->obj.type;
		rt->last_mat_cloned = false;
	}
	return (true);
}

char	*read_file_to_str(int fd)
{
	char	*content;
	off_t	size;
	ssize_t	n;

	size = lseek(fd, 0, SEEK_END);
	if (size <= 0)
		return (ft_strdup(""));
	lseek(fd, 0, SEEK_SET);
	content = malloc(size + 1);
	if (!content)
		return (NULL);
	n = read(fd, content, size);
	if (n < 0)
	{
		free(content);
		return (NULL);
	}
	content[n] = '\0';
	return (content);
}
