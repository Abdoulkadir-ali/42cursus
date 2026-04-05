/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:16:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	mesh_vertex_preview(t_mesh *m, t_mesh_sync s)
{
	size_t	vi;
	t_vec3	local;

	vi = 0;
	while (vi < m->vertex_count)
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
	while (vi < m->vertex_count)
		aabb_expand_point(&m->bbox, m->vertices[vi++].pos);
}

static t_mesh_sync	make_sync(t_mesh_group *g)
{
	t_mat4	sr;

	sr = mat4_mul(mat4_rotation(g->transform.rotation),
			mat4_scaling(g->transform.scale));
	return ((t_mesh_sync){sr,
			mat4_rotation(g->transform.rotation),
			g->pivot, g->transform.pos});
}

void	mesh_transform_sync(t_gui *gui)
{
	t_mesh_group	*g;
	t_scene			*sc;
	t_mesh_sync		s;
	size_t			si;

	if (!gui->selection.active || gui->selection.type != TYPE_MESH)
		return ;
	sc = gui->scene;
	if (gui->selection.index >= sc->group_count)
		return ;
	g = &sc->groups[gui->selection.index];
	if (g->start >= sc->mesh_count
		|| !sc->meshes[g->start].edit_snap_verts)
		return ;
	g->transform.pos = gui->transform.pos;
	g->transform.rotation = gui->transform.rotation;
	g->transform.scale = gui->transform.scale;
	s = make_sync(g);
	si = 0;
	while (si < g->sub_count)
	{
		if (sc->meshes[g->start + si].edit_snap_verts)
		{
			mesh_vertex_preview(&sc->meshes[g->start + si], s);
			mesh_build_bvh(&sc->meshes[g->start + si]);
		}
		si++;
	}
}

void	mesh_transform_commit(t_gui *gui)
{
	t_mesh_group	*g;
	t_scene			*sc;
	t_mesh_sync		s;
	size_t			si;

	if (!gui->selection.active || gui->selection.type != TYPE_MESH)
		return ;
	sc = gui->scene;
	if (gui->selection.index >= sc->group_count)
		return ;
	g = &sc->groups[gui->selection.index];
	if (g->start >= sc->mesh_count
		|| !sc->meshes[g->start].edit_snap_verts)
		return ;
	g->transform.pos = gui->transform.pos;
	g->transform.rotation = gui->transform.rotation;
	g->transform.scale = gui->transform.scale;
	s = make_sync(g);
	si = 0;
	while (si < g->sub_count)
	{
		if (sc->meshes[g->start + si].edit_snap_verts)
		{
			mesh_vertex_preview(&sc->meshes[g->start + si], s);
			mesh_build_bvh(&sc->meshes[g->start + si]);
		}
		si++;
	}
}
