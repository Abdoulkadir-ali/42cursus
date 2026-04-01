/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:09:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"


static bool	snap_alloc_geo(t_cache_snap *s, const t_mesh *m)
{
	s->vertices = malloc(sizeof(t_vec3) * m->vertex_count);
	if (!s->vertices)
		return (false);
	s->indices = malloc(sizeof(int) * m->tri_count * 3);
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
	if (!s->name || !snap_alloc_geo(s, m))
		return (false);
	ft_memcpy(s->vertices, m->vertices, sizeof(t_vec3) * m->vertex_count);
	ft_memcpy(s->indices, m->indices, sizeof(int) * m->tri_count * 3);
	if (m->normals)
		ft_memcpy(s->normals, m->normals, sizeof(t_vec3) * m->vertex_count);
	if (m->uvs)
		ft_memcpy(s->uvs, m->uvs, sizeof(t_vec2) * m->vertex_count);
	return (true);
}

bool	mesh_cache_save(t_scene *scene, const char *path, int start_mesh)
{
	t_model_cache	*entry;
	int				count;
	int				i;

	if (find_cache_idx(scene, NULL) == -2)
		return (true);
	count = scene->mesh_count - start_mesh;
	if (count <= 0)
		return (true);
	entry = get_cache_entry(scene, -2);
	if (!entry)
		return (true);
	ft_strlcpy(entry->path, path, sizeof(entry->path));
	entry->snaps = malloc(sizeof(t_cache_snap) * count);
	if (!entry->snaps)
		return (true);
	entry->count = 0;
	i = -1;
	while (++i < count)
	{
		if (!snap_one(&entry->snaps[i], &scene->meshes[start_mesh + i]))
			return (true);
		entry->count++;
	}
	return (true);
}
