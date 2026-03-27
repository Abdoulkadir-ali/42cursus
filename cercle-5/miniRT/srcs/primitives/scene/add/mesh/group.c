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
	int		si;

	g->sub_count = sc->mesh_count - g->start;
	g->anim_base = sc->meshes[g->start].anim_base;
	g->anim_clip_count = sc->meshes[g->start].anim_clip_count;
	bbox = sc->meshes[g->start].bbox;
	si = g->start + 1;
	while (si < sc->mesh_count)
		bbox = aabb_union(&bbox, &sc->meshes[si++].bbox);
	g->pivot = vec3((bbox.min.x + bbox.max.x) * HALF_SCALE,
			(bbox.min.y + bbox.max.y) * HALF_SCALE,
			(bbox.min.z + bbox.max.z) * HALF_SCALE);
	g->transform.scale = vec3(1, 1, 1);
}

bool	scene_add_group_for_subs(t_scene *scene, const char *path,
		int start_mesh)
{
	t_mesh_group	g;

	if (scene->mesh_count <= start_mesh)
		return (false);
	ft_memset(&g, 0, sizeof(g));
	g.start = start_mesh;
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
