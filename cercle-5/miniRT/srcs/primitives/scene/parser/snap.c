/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:13:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	refresh_mesh_snaps(t_scene *scene, size_t start_idx)
{
	t_mesh	*m;
	size_t	i;

	i = start_idx;
	while (i < scene->mesh_count)
	{
		m = &scene->meshes[i];
		if (m->edit_snap_verts)
			ft_memcpy(m->edit_snap_verts, m->vertices,
				sizeof(t_vertex) * m->vertex_count);
		if (m->normals && m->edit_snap_norms)
			ft_memcpy(m->edit_snap_norms, m->normals,
				sizeof(t_vec3) * m->vertex_count);
		m->edit_snap_pivot = vec3(
				(m->bbox.min.x + m->bbox.max.x) * 0.5,
				(m->bbox.min.y + m->bbox.max.y) * 0.5,
				(m->bbox.min.z + m->bbox.max.z) * 0.5);
		i++;
	}
}

static void	update_group_pivot(t_mesh_group *g, t_scene *scene)
{
	t_aabb	bbox;
	size_t	i;

	bbox = scene->meshes[g->start].bbox;
	i = g->start + 1;
	while (i < (g->start + g->sub_count)
		&& i < scene->mesh_count)
	{
		bbox = aabb_union(&bbox, &scene->meshes[i].bbox);
		i++;
	}
	g->pivot = vec3(
			(bbox.min.x + bbox.max.x) * 0.5,
			(bbox.min.y + bbox.max.y) * 0.5,
			(bbox.min.z + bbox.max.z) * 0.5);
}

void	refresh_editor_snaps(t_scene *scene, size_t start_idx)
{
	size_t	y;

	refresh_mesh_snaps(scene, start_idx);
	y = 0;
	while (y < scene->group_count)
	{
		if (scene->groups[y].start >= start_idx)
			update_group_pivot(&scene->groups[y], scene);
		y++;
	}
}
