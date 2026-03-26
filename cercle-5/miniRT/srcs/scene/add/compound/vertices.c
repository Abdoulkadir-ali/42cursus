/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "physics.h"

/**
 * @brief Mètre Ruban: Calculates the exact local AABB of a mesh.
 * Iterates through all vertices to find the min/max bounds.
 */
void	compute_mesh_aabb(t_mesh *mesh, t_aabb *out)
{
	int	i;

	if (!mesh || !mesh->vertices || mesh->vertex_count == 0)
	{
		out->min = vec3(-0.5, -0.5, -0.5);
		out->max = vec3(0.5, 0.5, 0.5);
		return ;
	}
	out->min = mesh->vertices[0];
	out->max = mesh->vertices[0];
	i = 0;
	while (++i < mesh->vertex_count)
	{
		out->min.x = fmin(out->min.x, mesh->vertices[i].x);
		out->min.y = fmin(out->min.y, mesh->vertices[i].y);
		out->min.z = fmin(out->min.z, mesh->vertices[i].z);
		out->max.x = fmax(out->max.x, mesh->vertices[i].x);
		out->max.y = fmax(out->max.y, mesh->vertices[i].y);
		out->max.z = fmax(out->max.z, mesh->vertices[i].z);
	}
}

/**
 * @brief Sets default AABB for primitive shapes based on their type.
 */
void	compute_primitive_aabb(t_sub_shape *s)
{
	if (s->type == TYPE_PHYS_SPHERE)
	{
		s->local_aabb.min = vec3(-1, -1, -1);
		s->local_aabb.max = vec3(1, 1, 1);
	}
	else if (s->type == TYPE_PHYS_BOX || s->type == TYPE_PHYS_PYRAMID)
	{
		s->local_aabb.min = vec3(-1, -1, -1);
		s->local_aabb.max = vec3(1, 1, 1);
	}
	else if (s->type == TYPE_PHYS_CAPSULE || s->type == TYPE_PHYS_CYLINDER)
	{
		s->local_aabb.min = vec3(-1, -2, -1);
		s->local_aabb.max = vec3(1, 2, 1);
	}
}
