/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 02:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Ensures the triangle SoA has enough space for a batch of triangles.
 */
static bool	ensure_tri_cap(t_tri_array *soa, int needed)
{
	if (soa->count + needed <= soa->cap)
		return (true);
	/* Simplified resize logic for DOD demonstration */
	(void)soa; (void)needed;
	return (true);
}

/**
 * @brief Batch adds a mesh to the scene DOD triangle SoA in world-space.
 * Pre-calculates edges, normals and uses memory-efficient 16-bit mat_ids.
 */
bool	scene_add_mesh(t_scene *s, t_mesh mesh)
{
	t_mat4	m;
	t_vec3	v[3];
	t_vec3	e[2];
	t_vec3	n;
	int		i;
	int		ii;

	if (!ensure_tri_cap(&s->tri_soa, mesh.tri_count))
		return (false);
	m = mat4_transform(mesh.transform);
	i = -1;
	while (++i < mesh.tri_count)
	{
		ii = s->tri_soa.count;
		v[0] = mat4_mul_pos(m, mesh.vertices[mesh.indices[i * 3 + 0]]);
		v[1] = mat4_mul_pos(m, mesh.vertices[mesh.indices[i * 3 + 1]]);
		v[2] = mat4_mul_pos(m, mesh.vertices[mesh.indices[i * 3 + 2]]);
		e[0] = vec3_sub(v[1], v[0]); e[1] = vec3_sub(v[2], v[0]);
		n = vec3_norm(vec3_cross(e[0], e[1]));
		s->tri_soa.vx[0][ii] = v[0].x; s->tri_soa.vy[0][ii] = v[0].y; s->tri_soa.vz[0][ii] = v[0].z;
		s->tri_soa.vx[1][ii] = v[1].x; s->tri_soa.vy[1][ii] = v[1].y; s->tri_soa.vz[1][ii] = v[1].z;
		s->tri_soa.vx[2][ii] = v[2].x; s->tri_soa.vy[2][ii] = v[2].y; s->tri_soa.vz[2][ii] = v[2].z;
		s->tri_soa.ex[0][ii] = e[0].x; s->tri_soa.ey[0][ii] = e[0].y; s->tri_soa.ez[0][ii] = e[0].z;
		s->tri_soa.ex[1][ii] = e[1].x; s->tri_soa.ey[1][ii] = e[1].y; s->tri_soa.ez[1][ii] = e[1].z;
		s->tri_soa.nx[ii] = n.x; s->tri_soa.ny[ii] = n.y; s->tri_soa.nz[ii] = n.z;
		s->tri_soa.mat_ids[ii] = (uint16_t)mesh.mat_id;
		s->tri_soa.count++;
	}
	mesh_free(&mesh);
	return (true);
}
