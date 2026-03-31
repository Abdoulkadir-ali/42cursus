/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

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

/**
 * Builds a local t_mesh_group structure without scene dependency.
 * The scene layer will be responsible for final injection.
 */
t_mesh_group	mesh_build_group(const char *path, int mesh_start,
					int mesh_count)
{
	t_mesh_group	g;

	ft_memset(&g, 0, sizeof(g));
	set_group_name(&g, path);
	g.mesh_start = mesh_start;
	g.mesh_count = mesh_count;
	g.transform.scale = vec3(1, 1, 1);
	return (g);
}
