/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	mesh_vertex_sync(t_mesh *m, t_mesh_sync s)
{
	int		vi;
	t_vec3	local;

	vi = 0;
	while ((size_t)vi < m->vertex_count)
	{
		local = vec3_sub(m->edit_snap_verts[vi].pos, s.piv);
		local = mat4_mul_pos(s.sr, local);
		m->vertices[vi].pos = vec3_add(vec3_add(local, s.piv), s.pos);
		if (m->normals && m->edit_snap_norms)
			m->normals[vi] = vec3_norm(mat4_mul_vec3(s.r,
						m->edit_snap_norms[vi]));
		vi++;
	}
	m->bbox = aabb_create_empty();
	vi = 0;
	while ((size_t)vi < m->vertex_count)
		aabb_expand_point(&m->bbox, m->vertices[vi++].pos);
	mesh_build_bvh(m);
}

void	mesh_transform_sync(t_gui *gui)
{
	t_mesh_group	*g;
	t_scene			*sc;
	t_mat4			sr;
	int				si;

	if (!gui->selection.active || gui->selection.type != TYPE_MESH)
		return ;
	sc = gui->scene;
	if (gui->selection.index >= sc->group_count)
		return ;
	g = &sc->groups[gui->selection.index];
	if ( g->start >= sc->mesh_count
		|| !sc->meshes[g->start].edit_snap_verts)
		return ;
	sr = mat4_mul(mat4_rotation(g->transform.rotation),
			mat4_scaling(g->transform.scale));
	si = 0;
	while ((size_t)si < g->sub_count)
	{
		if (sc->meshes[g->start + si].edit_snap_verts)
			mesh_vertex_sync(&sc->meshes[g->start + si], (t_mesh_sync){sr,
				mat4_rotation(g->transform.rotation), g->pivot,
				g->transform.pos});
		si++;
	}
}
