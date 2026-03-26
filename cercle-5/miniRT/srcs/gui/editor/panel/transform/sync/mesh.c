/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
static void	apply_vtx_tr(t_mesh *m, t_mat4 sr, t_mat4 r, t_vec3 piv_pos[2])
{
	int		vi;
	t_vec3	local;

	vi = 0;
	while (vi < m->vertex_count)
	{
		local = vec3_sub(m->edit_snap_verts[vi], piv_pos[0]);
		local = mat4_mul_pos(sr, local);
		m->vertices[vi] = vec3_add(vec3_add(local, piv_pos[0]), piv_pos[1]);
		if (m->normals && m->edit_snap_norms)
			m->normals[vi] = vec3_norm(mat4_mul_vec3(r, m->edit_snap_norms[vi]));
		vi++;
	}
	m->bbox = aabb_create_empty();
	vi = 0;
	while (vi < m->vertex_count)
		aabb_expand_point(&m->bbox, m->vertices[vi++]);
	mesh_build_bvh(m);
}

/**
 * @brief Synchronizes vertex data of a mesh group with its current transform.
 * @param gui Pointer to the GUI context.
 */
void	mesh_transform_sync(t_gui *gui)
{
	t_mesh_group	*g;
	t_mat4			sr[2];
	t_vec3			piv_pos[2];
	int				si;

	if (!gui->selection.active || gui->selection.type != TYPE_MESH)
		return ;
	g = &gui->scene->groups[gui->selection.index];
	if (!gui->scene->meshes[g->start].edit_snap_verts)
		return ;
	sr[0] = mat4_scaling(g->transform.scale);
	sr[1] = mat4_rotation(g->transform.rotation);
	piv_pos[0] = g->pivot;
	piv_pos[1] = g->transform.pos;
	si = 0;
	while (si < g->sub_count)
	{
		if (gui->scene->meshes[g->start + si].edit_snap_verts)
			apply_vtx_tr(&gui->scene->meshes[g->start + si],
				mat4_mul(sr[1], sr[0]), sr[1], piv_pos);
		si++;
	}
}
