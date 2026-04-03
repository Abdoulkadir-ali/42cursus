/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:11:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:27:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	process_mesh_triangles(const t_sphere *s, t_mesh *m,
				t_mbvh_node *node, t_collision *col)
{
	size_t	i;
	size_t	tri_idx;
	t_vec3	v[3];

	i = 0;
	while (i < node->count)
	{
		tri_idx = m->bvh_indices[node->left_or_first + i];
		v[0] = m->vertices[m->indices[tri_idx * 3 + 0]].pos;
		v[1] = m->vertices[m->indices[tri_idx * 3 + 1]].pos;
		v[2] = m->vertices[m->indices[tri_idx * 3 + 2]].pos;
		if (test_sphere_triangle(s, v, col))
		{
			col->hit = true;
			col->best_normal = col->normal;
			col->best_pen = col->pen;
		}
		i++;
	}
}

static void	traverse_mesh_bvh(const struct s_sphere *s, t_mesh *m,
				t_aabb s_aabb, t_collision *col)
{
	t_mbvh_node	*stack[64];
	int			top;
	t_mbvh_node	*node;

	top = 0;
	stack[top++] = &m->bvh_nodes[0];
	while (top > 0)
	{
		node = stack[--top];
		if (!mesh_aabb_overlap(&node->bbox, &s_aabb))
			continue ;
		if (node->count > 0)
			process_mesh_triangles(s, m, node, col);
		else
		{
			stack[top++] = &m->bvh_nodes[node->left_or_first];
			stack[top++] = &m->bvh_nodes[node->left_or_first + 1];
		}
	}
}

/**
 * Traverses the mesh BVH to check for collisions with a sphere.
 */
/**
 * Traverses the mesh BVH to check for collisions with a sphere.
 */
bool	detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
			t_physic_engine *en, t_collision *out)
{
	t_aabb		s_aabb;
	t_collision	col;

	if (en->settings.mesh_simplify_collision
		&& m->collider.type == COLLIDER_CAPSULE)
		return (detect_sphere_capsule_collision(s, &m->collider, out));
	if (!m || !m->bvh_nodes)
		return (false);
	s_aabb = sphere_aabb((t_sphere *)s);
	if (!mesh_aabb_overlap(&m->bbox, &s_aabb))
		return (false);
	ft_memset(&col, 0, sizeof(t_collision));
	col.min_dist_sq = 1e30;
	traverse_mesh_bvh(s, m, s_aabb, &col);
	if (col.hit && out)
	{
		out->best_normal = col.best_normal;
		out->best_pen = col.best_pen;
	}
	return (col.hit);
}
