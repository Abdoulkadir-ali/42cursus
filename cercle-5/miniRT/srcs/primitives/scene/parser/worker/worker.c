/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"
#include "physics.h"

static void	inject_sb(t_scene *sc, t_rt *rt, t_rt_line_task *t, size_t i)
{
	t_sb_params	p;

	scene_inject_mesh_resource_unique(sc, &t->resources[i],
		&t->results[i].data.mesh_info);
	p.mesh_idx = sc->mesh_count - 1;
	p.stiffness = t->results[i].data.mesh_info.sb_stiffness;
	p.damping = t->results[i].data.mesh_info.sb_damping;
	p.offset = t->results[i].data.mesh_info.transform.pos;
	scene_build_soft_body(sc, p);
	rt->last_type = TYPE_SOFT_BODY;
	rt->last_mat_cloned = false;
}

static void	inject_one(t_scene *sc, t_rt *rt, t_rt_line_task *t, size_t i)
{
	if (t->results[i].type == TYPE_MAT_MOD)
		apply_mat_mod_to_last(sc, rt, &t->results[i].data.mat_mod);
	else if (t->results[i].type == TYPE_MESH)
	{
		scene_inject_mesh_resource(sc, &t->resources[i],
			&t->results[i].data.mesh_info);
		rt->last_type = TYPE_MESH;
		rt->last_mat_cloned = false;
	}
	else if (t->results[i].type == TYPE_SOFT_BODY)
		inject_sb(sc, rt, t, i);
	else if (process_object(sc, t->results[i]))
	{
		rt->last_type = t->results[i].type;
		rt->last_mat_cloned = false;
	}
}

void	cleanup_task(t_rt_line_task *t);
bool	prep_task(t_rt_line_task *t, char *content);

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
			inject_one(sc, &rt, t, i);
		free(t->lines[i++]);
	}
	cleanup_task(t);
}

bool	parse_rt_worker(const char *path, t_scene *scene)
{
	t_rt_line_task	t;
	char			*content;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	content = read_file_to_str(fd);
	close(fd);
	if (!content || !prep_task(&t, content))
		return (false);
	t.pool = scene->pool;
	t.next_idx = 0;
	parallel_run(scene->pool, t.count, rt_worker, &t);
	t.next_idx = 0;
	parallel_run(scene->pool, t.count, rt_mesh_worker, &t);
	return (inject_results(scene, &t), true);
}
