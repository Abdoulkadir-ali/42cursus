/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Helper function to process leaf nodes for occlusion.
*/
static bool	process_leaf(const t_bvh_node *node, const t_ray *ray,
		const t_bvh *bvh, double max_t)
{
	size_t	i;
	t_hit	temp;

	i = 0;
	while (i < node->num_refs)
	{
		if (node->refs[i].type == TYPE_MESH)
		{
			if (mesh_occluded(ray, &bvh->scene->meshes[node->refs[i].index],
					max_t))
				return (true);
		}
		else if (node->refs[i].type == TYPE_ANIM)
		{
			if (mesh_occluded(ray,
					&bvh->scene->animated[node->refs[i].index].base, max_t))
				return (true);
		}
		else if (intersect_object(ray, bvh->scene, node->refs[i], &temp)
			&& temp.t > EPSILON && temp.t < max_t)
			return (true);
		i++;
	}
	return (false);
}

/*
** Iterative traversal for shadow rays (any hit).
*/
static void	process_internal_node_occluded(t_bvh_node *node,
		t_bvh_node *stack[128], int *ptr)
{
	if (*ptr >= 126)
		return ;
	if (node->right)
		stack[(*ptr)++] = node->right;
	if (node->left)
		stack[(*ptr)++] = node->left;
}

static bool	traverse_bvh_occluded(const t_bvh *bvh, const t_ray *ray,
		double max_t)
{
	t_bvh_node	*stack[128];
	int			ptr;
	t_bvh_node	*node;
	tvec2		t_times;
	bool		intersects;

	ptr = 0;
	stack[ptr++] = bvh->root;
	while (ptr > 0)
	{
		node = stack[--ptr];
		intersects = aabb_intersect_fast(&node->bbox, ray, &t_times.x,
				&t_times.y);
		if (!intersects || t_times.x > max_t)
			continue ;
		if (node->left || node->right)
			process_internal_node_occluded(node, stack, &ptr);
		else
		{
			if (process_leaf(node, ray, bvh, max_t))
				return (true);
		}
	}
	return (false);
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	if (!bvh || !bvh->root)
		return (false);
	return (traverse_bvh_occluded(bvh, ray, max_t));
}
