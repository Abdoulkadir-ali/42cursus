/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:02:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static t_mat4	*get_joint_matrix(t_mesh *mesh, size_t joint_idx)
{
	if (joint_idx == (size_t)-1 || joint_idx >= mesh->bone_count)
		return (NULL);
	return (&mesh->bone_matrices[joint_idx]);
}

static void	apply_skin_norm(t_vec3 *n_src, t_mat4 *mat, float w, t_vec3 *norm)
{
	t_vec3	p;

	if (n_src)
		p = mat4_mul_dir(*mat, *n_src);
	else
		p = mat4_mul_dir(*mat, vec3(0, 1, 0));
	norm->x += p.x * w;
	norm->y += p.y * w;
	norm->z += p.z * w;
}

static void	apply_skin_vertex(t_mesh *m, int i, t_vec3 *pos, t_vec3 *norm)
{
	t_bone_weight	*bw;
	t_mat4			*mat;
	t_vec3			p;
	int				k;

	bw = &m->weights[i];
	*pos = vec3(0, 0, 0);
	*norm = vec3(0, 0, 0);
	k = -1;
	while (++k < 4)
	{
		mat = get_joint_matrix(m, bw->bone_indices[k]);
		if (!mat || bw->weights[k] <= 0.0f)
			continue ;
		p = mat4_mul_dir(*mat, m->base_geometry.vertices[i]);
		pos->x += p.x * bw->weights[k];
		pos->y += p.y * bw->weights[k];
		pos->z += p.z * bw->weights[k];
		if (m->base_normals)
			apply_skin_norm(&m->base_normals[i], mat, bw->weights[k], norm);
		else
			apply_skin_norm(NULL, mat, bw->weights[k], norm);
	}
}

/**
 * Performs linear blend skinning (LBS) on a mesh using its skeleton matrices.
 */
static void	update_mesh_vertex(t_mesh *mesh, int i)
{
	t_vec3	pos;
	t_vec3	norm;

	apply_skin_vertex(mesh, i, &pos, &norm);
	mesh->geometry.vertices[i] = pos;
	if (mesh->normals)
		mesh->normals[i] = norm;
}

void	glb_skin_mesh(t_mesh *mesh)
{
	size_t		i;

	if (!mesh->weights || !mesh->skeleton)
		return ;
	i = 0;
	while (i < mesh->base_geometry.vertex_count)
	{
		update_mesh_vertex(mesh, i);
		i++;
	}
}
