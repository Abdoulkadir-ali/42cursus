/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:16:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "debug.h"

static void	init_editor_snapshot(t_mesh *mesh)
{
	size_t	size;

	if (!mesh->edit_snap_verts)
	{
		size = sizeof(t_vertex) * mesh->vertex_count;
		mesh->edit_snap_verts = malloc(size);
		if (mesh->edit_snap_verts)
			ft_memcpy(mesh->edit_snap_verts, mesh->vertices, size);
	}
	if (mesh->normals && !mesh->edit_snap_norms)
	{
		size = sizeof(t_vec3) * mesh->vertex_count;
		mesh->edit_snap_norms = malloc(size);
		if (mesh->edit_snap_norms)
			ft_memcpy(mesh->edit_snap_norms, mesh->normals, size);
	}
	mesh->edit_snap_pivot = vec3((mesh->bbox.min.x + mesh->bbox.max.x) * 0.5,
			(mesh->bbox.min.y + mesh->bbox.max.y) * 0.5,
			(mesh->bbox.min.z + mesh->bbox.max.z) * 0.5);
}

static void	init_phys_collider(t_mesh *mesh)
{
	double	w_x;
	double	w_z;
	double	radius;
	double	cx;
	double	cz;

	mesh->phys.is_static = true;
	mesh->phys.mass = 0.0;
	mesh->phys.restitution = 0.5;
	mesh->collider.type = COLLIDER_CAPSULE;
	w_x = mesh->bbox.max.x - mesh->bbox.min.x;
	w_z = mesh->bbox.max.z - mesh->bbox.min.z;
	if (w_x < w_z)
		radius = w_x * 0.5;
	else
		radius = w_z * 0.5;
	cx = (mesh->bbox.min.x + mesh->bbox.max.x) * 0.5;
	cz = (mesh->bbox.min.z + mesh->bbox.max.z) * 0.5;
	mesh->collider.data.capsule.radius = radius;
	mesh->collider.data.capsule.a = vec3(cx, mesh->bbox.min.y, cz);
	mesh->collider.data.capsule.b = vec3(cx, mesh->bbox.max.y, cz);
}

static void	apply_vertex_transform(t_mesh *m, t_mat4 mat, t_mat4 rot)
{
	int	i;

	i = 0;
	while (i < m->vertex_count)
	{
		m->vertices[i].pos = mat4_mul_pos(mat, m->vertices[i].pos);
		if (m->normals)
		{
			m->normals[i] = mat4_mul_vec3(rot, m->normals[i]);
			m->normals[i] = vec3_norm(m->normals[i]);
		}
		i++;
	}
	m->bbox = aabb_create_empty();
	i = 0;
	while (i < m->vertex_count)
	{
		aabb_expand_point(&m->bbox, m->vertices[i].pos);
		i++;
	}
}

/**
 * Applies a baked transform to a mesh, modifying its vertices and normals 
 * permanently and rebuilding its BVH and physics collider.
 */
void	mesh_apply_transform(t_mesh *mesh, t_transform transform)
{
	t_mat4	m;
	t_mat4	rot;

	if (!mesh)
		return ;
	m = mat4_transform(transform);
	rot = mat4_rotation(transform.rotation);
	apply_vertex_transform(mesh, m, rot);
	init_editor_snapshot(mesh);
	init_phys_collider(mesh);
	mesh->scene_mat = m;
	mesh->scene_rot_mat = rot;
	mesh->has_scene_transform = true;
	mesh->transform = (t_transform){0};
	mesh->transform.scale = vec3(1, 1, 1);
	mesh_build_bvh(mesh);
}
