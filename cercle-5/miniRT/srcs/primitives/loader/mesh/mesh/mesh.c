/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:52:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static void	*grow(void *ptr, size_t n)
{
	return (realloc(ptr, n));
}

/**
 * @brief Synchronized parallel reallocation for the triangle SoA.
 */
static bool	realloc_tri_soa(t_tri_array *soa, size_t new_cap)
{
	int		k;
	size_t	sz;

	sz = new_cap * sizeof(float);
	k = -1;
	while (++k < 3)
	{
		soa->vx[k] = grow(soa->vx[k], sz);
		soa->vy[k] = grow(soa->vy[k], sz);
		soa->vz[k] = grow(soa->vz[k], sz);
	}
	k = -1;
	while (++k < 2)
	{
		soa->ex[k] = grow(soa->ex[k], sz);
		soa->ey[k] = grow(soa->ey[k], sz);
		soa->ez[k] = grow(soa->ez[k], sz);
	}
	soa->nx = grow(soa->nx, sz);
	soa->ny = grow(soa->ny, sz);
	soa->nz = grow(soa->nz, sz);
	soa->mat_ids = grow(soa->mat_ids, new_cap * sizeof(uint16_t));
	soa->cap = new_cap;
	return (soa->nx != NULL && soa->mat_ids != NULL);
}

/**
 * @brief DOD-compliant dynamic growth for the triangle SoA.
 */
static bool	ensure_tri_cap(t_tri_array *soa, size_t needed)
{
	size_t	n;

	if (soa->count + needed <= soa->cap)
		return (true);
	n = soa->cap;
	if (n == 0)
		n = 1024 * 32; /* Initial large chunk for meshes */
	while (n < soa->count + needed)
		n *= 2;
	return (realloc_tri_soa(soa, n));
}

static bool	add_mesh_instance_meta(t_scene *s, t_mesh_asset *mesh)
{
	t_mesh_instance_metadata	*m;
	t_mesh_instance_metadata	**nm;
	size_t				idx;

	m = ft_calloc(1, sizeof(t_mesh_instance_metadata));
	if (!m)
		return (false);
	m->orig_transform = mat4_transform(mesh->transform);
	m->import_time = time(NULL);
	if (mesh->name)
		m->file_path = ft_strdup(mesh->name);
	if (mesh->name && !m->file_path)
		return (free(m), false);
	idx = s->mesh_count;
	nm = realloc(s->mesh_instance_meta, (idx + 1) * sizeof(t_mesh_instance_metadata *));
	if (!nm)
		return (free(m->file_path), free(m), false);
	s->mesh_instance_meta = nm;
	s->mesh_instance_meta[idx] = m;
	s->mesh_count = idx + 1;
	return (true);
}

static void	pop_mesh_instance_meta(t_scene *s)
{
	size_t	idx;

	if (!s->mesh_instance_meta || s->mesh_count == 0)
		return ;
	idx = s->mesh_count - 1;
	if (s->mesh_instance_meta[idx])
	{
		free(s->mesh_instance_meta[idx]->file_path);
		free(s->mesh_instance_meta[idx]);
	}
	s->mesh_instance_meta[idx] = NULL;
	s->mesh_count = idx;
}

/**
 * @brief Batch adds a mesh to the scene DOD triangle SoA in world-space.
 */
bool	scene_add_mesh(t_scene *s, t_mesh_asset mesh)
{
	t_mat4	m;
	t_vec3	v[3];
	t_vec3	e[2];
	t_vec3	n;
	size_t	i;
	size_t	ii;

	if (mesh.bone_ids != NULL)
	{
		t_skinned_mesh sm;
		ft_memset(&sm, 0, sizeof(t_skinned_mesh));
		sm.base_vertices = mesh.vertices;
		sm.vertices = ft_calloc(mesh.vertex_count, sizeof(t_vec3));
		sm.base_normals = mesh.normals;
		sm.normals = ft_calloc(mesh.vertex_count, sizeof(t_vec3));
		sm.bone_ids = mesh.bone_ids;
		sm.weights = mesh.weights;
		sm.weight_counts = mesh.weight_counts;
		sm.weight_offsets = mesh.weight_offsets;
		sm.vertex_count = (int)mesh.vertex_count;
		sm.mat_id = mesh.mat_id;
		sm.bbox = mesh.bbox;
		sm.skeleton_dirty = true;
		if (!add_mesh_instance_meta(s, &mesh))
			return (mesh_free(&mesh), false);
		free(mesh.name);
		free(mesh.indices);
		if (!scene_add_animated(s, sm))
			return (pop_mesh_instance_meta(s), false);
		return (true);
	}
	if (!ensure_tri_cap(&s->tri_soa, mesh.tri_count))
		return (false);
	if (!add_mesh_instance_meta(s, &mesh))
		return (mesh_free(&mesh), false);
	m = mat4_transform(mesh.transform);
	i = 0;
	while (i < mesh.tri_count)
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
		s->tri_soa.count++; i++;
	}
	mesh_free(&mesh);
	return (true);
}
