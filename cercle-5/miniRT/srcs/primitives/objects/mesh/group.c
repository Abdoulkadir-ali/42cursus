/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:43:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	set_group_name(t_mesh_group *g, const char *path)
{
	const char	*slash;
	char		*dot;

	if (!path || !*path)
	{
		g->name = ft_strdup("default_group");
		return ;
	}
	slash = ft_strrchr(path, '/');
	if (slash)
		g->name = ft_strdup(slash + 1);
	else
		g->name = ft_strdup(path);
	if (!g->name)
		return ;
	dot = ft_strrchr(g->name, '.');
	if (dot)
		*dot = '\0';
}

/*
** Builds a t_mesh_group from the submeshes in
** scene->meshes[start_mesh .. mesh_count-1]
** and appends it to scene->groups[].
*/
bool	scene_add_group_for_subs(t_scene *scene, const char *path,
			size_t start_mesh)
{
	t_mesh_group	g;

	if (scene->mesh_count <= start_mesh)
		return (false);
	ft_memset(&g, 0, sizeof(g));
	set_group_name(&g, path);
	if (!g.name)
		return (false);
	g.mesh_start = start_mesh;
	g.mesh_count = scene->mesh_count - start_mesh;
	g.transform.scale = vec3(1, 1, 1);
	return (scene_add_group(scene, g));
}
