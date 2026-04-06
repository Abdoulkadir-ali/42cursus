/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 19:08:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

static void	init_p_line(t_parser *p, char *line)
{
	ft_memset(p, 0, sizeof(t_parser));
	p->fd = -1;
	p->eof = true;
	p->bytes_read = ft_strlen(line);
	if (p->bytes_read > PARSER_BUF_SIZE)
		p->bytes_read = PARSER_BUF_SIZE;
	ft_memcpy(p->buffer, line, p->bytes_read);
	p->buffer[p->bytes_read] = '\0';
}

static void	*rt_worker(void *ptr)
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

static void	*rt_mesh_worker(void *ptr)
{
	t_rt_line_task	*t;
	size_t			i;

	t = (t_rt_line_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&t->next_idx, 1);
		if (i >= t->count)
			break ;
		if (t->statuses[i] && t->results[i].type == TYPE_MESH)
			mesh_build_resource(NULL, t->results[i].data.mesh_info.path,
				&t->resources[i]);
	}
	return (NULL);
}

static void	inject_results(t_scene *sc, t_rt_line_task *t)
{
	size_t	i;
	t_rt	rt;

	ft_memset(&rt, 0, sizeof(rt));
	rt.last_type = TYPE_NONE;
	i = 0;
	while (i < t->count)
	{
		if (t->statuses[i])
		{
			if (t->results[i].type == TYPE_MAT_MOD)
				apply_mat_mod_to_last(sc, &rt, &t->results[i].data.mat_mod);
			else if (t->results[i].type == TYPE_MESH)
			{
				scene_inject_mesh_resource(sc, &t->resources[i],
					&t->results[i].data.mesh_info);
				rt.last_type = TYPE_MESH;
				rt.last_mat_cloned = false;
			}
			else
			{
				if (process_object(sc, t->results[i]))
				{
					rt.last_type = t->results[i].type;
					rt.last_mat_cloned = false;
				}
			}
		}
		free(t->lines[i++]);
	}
	free(t->lines);
	free(t->results);
	free(t->statuses);
	free(t->resources);
}

bool	parse_rt_worker(const char *path, t_scene *scene)
{
	int				fd;
	t_rt_line_task	t;
	char			*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	content = read_file_to_str(fd);
	close(fd);
	if (!content)
		return (false);
	t.lines = ft_split(content, '\n');
	free(content);
	if (!t.lines)
		return (false);
	t.count = 0;
	while (t.lines[t.count])
		t.count++;
	t.results = ft_calloc(t.count, sizeof(t_parse_obj));
	t.statuses = ft_calloc(t.count, sizeof(bool));
	t.resources = ft_calloc(t.count, sizeof(t_mesh_resource));
	t.pool = scene->pool;
	t.next_idx = 0;
	parallel_run(scene->pool, t.count, rt_worker, &t);
	t.next_idx = 0;
	parallel_run(scene->pool, t.count, rt_mesh_worker, &t);
	inject_results(scene, &t);
	return (true);
}
