/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 03:58:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"

#define CACHE_CAP 64

typedef struct s_mesh_snap
{
	char	*name;
	t_vec3	*vertices;
	t_vec3	*normals;
	t_vec2	*uvs;
	int		*indices;
	int		vertex_count;
	int		tri_count;
	int		mat_id;
}	t_mesh_snap;

typedef struct s_model_cache
{
	char		path[512];
	t_mesh_snap	*snaps;
	int			count;
}	t_model_cache;

static t_model_cache	g_cache[CACHE_CAP];
static int				g_cache_count = 0;

/*
** Returns index of path in cache, or -1.
*/
static int	find_cache_idx(const char *path)
{
	int	i;

	i = 0;
	while (i < g_cache_count)
	{
		if (ft_strcmp(g_cache[i].path, path) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	mesh_cache_has(const char *path)
{
	return (find_cache_idx(path) >= 0);
}

/*
** Deep-copies geometry arrays from mesh into snap.
** Returns false on allocation failure.
*/
static bool	snap_alloc_geo(t_mesh_snap *s, const t_mesh *m)
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

static bool	snap_one(t_mesh_snap *s, const t_mesh *m)
{
	ft_memset(s, 0, sizeof(*s));
	s->vertex_count = m->vertex_count;
	s->tri_count = m->tri_count;
	s->mat_id = m->mat_id;
	s->name = ft_strdup(m->name ? m->name : "");
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

/*
** Saves all meshes [start_mesh..scene->mesh_count) into the cache.
** Fails gracefully (returns true) — missing cache just means a re-parse
** on next occurrence, but the scene is unaffected.
*/
bool	mesh_cache_save(const char *path, t_scene *scene, int start_mesh)
{
	t_model_cache	*entry;
	int				count;
	int				i;

	if (g_cache_count >= CACHE_CAP)
		return (true);
	count = scene->mesh_count - start_mesh;
	if (count <= 0)
		return (true);
	entry = &g_cache[g_cache_count];
	ft_strlcpy(entry->path, path, sizeof(entry->path));
	entry->snaps = malloc(sizeof(t_mesh_snap) * count);
	if (!entry->snaps)
		return (true);
	entry->count = 0;
	i = 0;
	while (i < count)
	{
		if (!snap_one(&entry->snaps[i], &scene->meshes[start_mesh + i]))
			return (true);
		entry->count++;
		i++;
	}
	g_cache_count++;
	return (true);
}

/*
** Allocates and copies geometry from a snap into a fresh t_mesh.
*/
static bool	restore_geo(t_mesh *mesh, const t_mesh_snap *snap)
{
	mesh->vertices = malloc(sizeof(t_vec3) * snap->vertex_count);
	if (!mesh->vertices)
		return (mesh_free(mesh), false);
	ft_memcpy(mesh->vertices, snap->vertices, sizeof(t_vec3) * snap->vertex_count);
	mesh->indices = malloc(sizeof(int) * snap->tri_count * 3);
	if (!mesh->indices)
		return (mesh_free(mesh), false);
	ft_memcpy(mesh->indices, snap->indices, sizeof(int) * snap->tri_count * 3);
	if (snap->normals)
	{
		mesh->normals = malloc(sizeof(t_vec3) * snap->vertex_count);
		if (!mesh->normals)
			return (mesh_free(mesh), false);
		ft_memcpy(mesh->normals, snap->normals, sizeof(t_vec3) * snap->vertex_count);
	}
	if (snap->uvs)
	{
		mesh->uvs = malloc(sizeof(t_vec2) * snap->vertex_count);
		if (!mesh->uvs)
			return (mesh_free(mesh), false);
		ft_memcpy(mesh->uvs, snap->uvs, sizeof(t_vec2) * snap->vertex_count);
	}
	return (true);
}

static bool	restore_one(const t_mesh_snap *snap, t_scene *scene)
{
	t_mesh	mesh;
	int		inst_mat;

	ft_memset(&mesh, 0, sizeof(t_mesh));
	mesh.transform.scale = vec3(1, 1, 1);
	mesh.group_id = -1;
	mesh.vertex_count = snap->vertex_count;
	mesh.tri_count = snap->tri_count;
	inst_mat = scene_clone_material(scene, snap->mat_id);
	mesh.mat_id = (inst_mat >= 0) ? inst_mat : snap->mat_id;
	mesh.name = ft_strdup(snap->name ? snap->name : "");
	if (!mesh.name)
		return (false);
	if (!restore_geo(&mesh, snap))
		return (false);
	return (scene_add_mesh(scene, mesh));
}

/*
** Restores all snapped meshes for the given path into the scene.
*/
bool	mesh_cache_restore(const char *path, t_scene *scene)
{
	int	idx;
	int	i;

	idx = find_cache_idx(path);
	if (idx < 0)
		return (false);
	i = 0;
	while (i < g_cache[idx].count)
	{
		if (!restore_one(&g_cache[idx].snaps[i], scene))
			return (false);
		i++;
	}
	return (true);
}
