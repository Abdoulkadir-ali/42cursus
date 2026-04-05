/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 22:22:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	snap_alloc_geo(t_cache_snap *s, const t_mesh *m)
{
	s->vertices = malloc(sizeof(t_vertex) * m->vertex_count);
	if (!s->vertices)
		return (false);
	s->indices = malloc(sizeof(size_t) * m->tri_count * 3);
	if (!s->indices)
		return (false);
	if (m->normals)
	{
		s->normals = malloc(sizeof(t_vec3) * m->vertex_count);
		if (!s->normals)
			return (false);
	}
	if (m->uvs)
	{
		s->uvs = malloc(sizeof(t_vec2) * m->vertex_count);
		if (!s->uvs)
			return (false);
	}
	return (true);
}

static bool	snap_one_copy(t_cache_snap *s, const t_mesh *m)
{
	if (!s->name || !snap_alloc_geo(s, m))
		return (false);
	ft_memcpy(s->vertices, m->vertices, sizeof(t_vertex) * m->vertex_count);
	ft_memcpy(s->indices, m->indices, sizeof(size_t) * m->tri_count * 3);
	if (m->normals)
		ft_memcpy(s->normals, m->normals, sizeof(t_vec3) * m->vertex_count);
	if (m->uvs)
		ft_memcpy(s->uvs, m->uvs, sizeof(t_vec2) * m->vertex_count);
	return (true);
}

static bool	snap_one(t_cache_snap *s, const t_mesh *m)
{
	ft_memset(s, 0, sizeof(*s));
	s->vertex_count = m->vertex_count;
	s->tri_count = m->tri_count;
	s->mat_id = m->mat_id;
	if (m->name)
		s->name = ft_strdup(m->name);
	else
		s->name = ft_strdup("");
	return (snap_one_copy(s, m));
}

static bool	cache_save_loop(t_scene *scene, t_model_cache *entry,
				size_t start_mesh, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!snap_one(&entry->snaps[i], &scene->meshes[start_mesh + i]))
			return (true);
		entry->count++;
		i++;
	}
	return (true);
}

bool	mesh_cache_save(t_scene *scene, const char *path, size_t start_mesh)
{
	t_model_cache	*entry;
	size_t			count;

	if (scene->cache_count >= MAX_MODEL_CACHE)
		return (true);
	count = scene->mesh_count - start_mesh;
	if (count == 0)
		return (true);
	scene->cache_count++;
	entry = get_cache_entry(scene, scene->cache_count - 1);
	if (!entry)
		return (true);
	ft_strlcpy(entry->path, path, sizeof(entry->path));
	entry->snaps = malloc(sizeof(t_cache_snap) * count);
	if (!entry->snaps)
		return (true);
	entry->count = 0;
	return (cache_save_loop(scene, entry, start_mesh, count));
}
