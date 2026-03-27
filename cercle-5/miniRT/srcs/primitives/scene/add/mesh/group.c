/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:35:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	set_group_names(t_mesh_group *g, const char *path)
{
	const char	*slash;
	char		*dot;

	if (path)
		g->path = ft_strdup(path);
	else
		g->path = ft_strdup("");
	if (path)
		slash = ft_strrchr(path, '/');
	else
		slash = NULL;
	if (slash)
		g->name = ft_strdup(slash + 1);
	else if (path)
		g->name = ft_strdup(path);
	else
		g->name = ft_strdup("");
	if (!g->name || !g->path)
	{
		free(g->name);
		free(g->path);
		return (false);
	}
	dot = ft_strrchr(g->name, '.');
	if (dot)
		*dot = '\0';
	return (true);
}

static void	set_group_bounds(t_scene *sc, t_mesh_group *g)
{
	t_aabb	bbox;
	int		ti;

	g->tri_count = sc->tri_count - g->tri_start;
	if (g->tri_count <= 0)
		return ;
	bbox = aabb_create_empty();
	ti = g->tri_start;
	while (ti < sc->tri_count)
	{
		aabb_expand_point(&bbox, sc->triangles[ti].v[0]);
		aabb_expand_point(&bbox, sc->triangles[ti].v[1]);
		aabb_expand_point(&bbox, sc->triangles[ti].v[2]);
		ti++;
	}
	g->bbox = bbox;
	g->pivot = vec3((bbox.min.x + bbox.max.x) * 0.5,
			(bbox.min.y + bbox.max.y) * 0.5,
			(bbox.min.z + bbox.max.z) * 0.5);
	g->transform.scale = vec3(1, 1, 1);
}

bool	scene_add_group_for_subs(t_scene *scene, const char *path,
		int start_tri)
{
	t_mesh_group	g;

	if (scene->tri_count <= start_tri)
		return (false);
	ft_memset(&g, 0, sizeof(g));
	g.tri_start = start_tri;
	if (!set_group_names(&g, path))
		return (false);
	set_group_bounds(scene, &g);
	return (scene_add_group(scene, g));
}

bool	scene_add_group(t_scene *scene, t_mesh_group g)
{
	if (!DYNARRAY_ENSURE_INT(&scene->groups, &scene->group_count,
			&scene->group_cap, sizeof(t_mesh_group)))
		return (false);
	scene->groups[scene->group_count++] = g;
	return (true);
}
