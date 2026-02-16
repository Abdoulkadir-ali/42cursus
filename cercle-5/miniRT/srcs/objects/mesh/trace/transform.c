/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "raytracing.h"

static void	apply_mesh_transform(t_mesh *mesh, t_mat4 m, t_mat4 rot)
{
	int	i;

	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->vertices[i] = mat4_mul_pos(m, mesh->vertices[i]);
		if (mesh->normals)
		{
			mesh->normals[i] = mat4_mul_vec3(rot, mesh->normals[i]);
			mesh->normals[i] = vec3_norm(mesh->normals[i]);
		}
		i++;
	}
}

static void	update_mesh_bbox(t_mesh *mesh)
{
	int	i;

	mesh->bbox = aabb_create_empty();
	i = 0;
	while (i < mesh->vertex_count)
		aabb_expand_point(&mesh->bbox, mesh->vertices[i++]);
}

static void	reset_mesh_transform(t_mesh *mesh)
{
	mesh->transform = (t_transform){0};
	mesh->transform.scale = vec3(1, 1, 1);
}

void	mesh_apply_transform(t_mesh *mesh, t_transform transform)
{
	t_mat4	m;
	t_mat4	rot;

	if (!mesh)
		return ;
	debug_print_mesh_bake(mesh, true);
	m = mat4_transform(transform);
	rot = mat4_rotation(transform.rotation);
	apply_mesh_transform(mesh, m, rot);
	update_mesh_bbox(mesh);
	
	/* Initialize Physics Collider (Capsule Approximation) */
	mesh->phys.is_static = true; /* Environment mesh */
	mesh->phys.mass = 0.0;
	mesh->phys.elasticity = 0.5;
	mesh->collider.type = COLLIDER_CAPSULE;
	
	double width_x = mesh->bbox.max.x - mesh->bbox.min.x;
	double width_z = mesh->bbox.max.z - mesh->bbox.min.z;
	double radius = (width_x < width_z ? width_x : width_z) * 0.5;
	double cx = (mesh->bbox.min.x + mesh->bbox.max.x) * 0.5;
	double cz = (mesh->bbox.min.z + mesh->bbox.max.z) * 0.5;

	/* Shrink capsule slightly to fit inside AABB? Or match? */
	mesh->collider.data.capsule.radius = radius;
	mesh->collider.data.capsule.a = vec3(cx, mesh->bbox.min.y, cz);
	mesh->collider.data.capsule.b = vec3(cx, mesh->bbox.max.y, cz);

	reset_mesh_transform(mesh);
	mesh_build_bvh(mesh);
	debug_print_mesh_bake(mesh, false);
}
