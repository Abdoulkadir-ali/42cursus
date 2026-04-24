/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:48:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:33:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

static void	init_p_line(t_parser *p, char *line)
{
	p->fd = -1;
	p->eof = true;
	p->cursor = 0;
	p->bytes_read = ft_strlen(line);
	if (p->bytes_read > PARSER_BUF_SIZE)
		p->bytes_read = PARSER_BUF_SIZE;
	ft_memcpy(p->buffer, line, p->bytes_read);
	p->buffer[p->bytes_read] = '\0';
}

void	*rt_worker(void *ptr)
{
	t_rt_line_task	*t;
	size_t			i;
	t_parser		p;
	t_rt			rt;

	t = (t_rt_line_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&t->next_idx, 1);
		if (i >= t->count)
			break ;
		init_p_line(&p, t->lines[i]);
		rt.parser = &p;
		rt.status = true;
		if (read_id(rt.parser, rt.id, sizeof(rt.id)))
		{
			t->results[i] = dispatch_scan(rt.parser, rt.id);
			t->statuses[i] = (t->results[i].type != TYPE_NONE);
		}
		else
			t->statuses[i] = false;
	}
	return (NULL);
}

void	*rt_mesh_worker(void *ptr)
{
	t_rt_line_task	*t;
	size_t			i;

	t = (t_rt_line_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&t->next_idx, 1);
		if (i >= t->count)
			break ;
		if (t->statuses[i] && (t->results[i].type == TYPE_MESH
				|| t->results[i].type == TYPE_SOFT_BODY))
			mesh_build_resource(NULL, t->results[i].data.mesh_info.path,
				&t->resources[i]);
	}
	return (NULL);
}
