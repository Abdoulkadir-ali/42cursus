/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:11:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 12:40:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** OBJ meshes: t_vertex *vertices (field .pos) + t_triangle *triangles
** GLB meshes: t_mesh_geom geometry (t_vec3 *vertices, direct, no .pos)
** bvh_init_indices allocates m->indices for OBJ too, so branching on
** m->indices no longer identifies the model.  Use m->vertices != NULL.
*/
static t_vec3	mesh_vtx_pos(const t_mesh *m, size_t idx)
{
	if (m->vertices)
		return (m->vertices[idx].pos);
	return (m->geometry.vertices[idx]);
}

static void	process_mesh_triangles(const t_sphere *s, t_mesh *m,
				t_mbvh_node *node, t_collision *col)
{
	size_t	i;
	size_t	base;
	t_vec3	v[3];

	i = 0;
	while (i < node->count)
	{
		base = (node->left_or_first + i) * 3;
		v[0] = mesh_vtx_pos(m, m->bvh_indices[base + 0]);
		v[1] = mesh_vtx_pos(m, m->bvh_indices[base + 1]);
		v[2] = mesh_vtx_pos(m, m->bvh_indices[base + 2]);
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
	t_mbvh_node	*stack[MESH_BVH_STACK_SIZE];
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
		else if (top < MESH_BVH_STACK_SIZE - 2)
		{
			stack[top++] = &m->bvh_nodes[(size_t)(node - m->bvh_nodes) + 1];
			stack[top++] = &m->bvh_nodes[node->left_or_first];
		}
	}
}

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
	if (!m->vertices && !m->geometry.vertices)
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
