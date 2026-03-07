/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	traverse_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_bvh_node	*stack[128];
	int			ptr;
	t_bvh_node	*node;
	t_vec2		t_times;
	bool		intersects;

	ptr = 0;
	stack[ptr++] = bvh->root;
	while (ptr > 0)
	{
		node = stack[--ptr];
		intersects = aabb_intersect_fast(&node->bbox, ray, &t_times.x,
				&t_times.y);
		t_times.x = (t_times.x < 0.0) ? 0.0 : t_times.x;
		if (!intersects || t_times.x > hit->t)
			continue ;
		if (node->left || node->right)
			process_internal_node(node, stack, &ptr, ray);
		else
			process_leaf(node, ray, bvh, hit);
	}
	return (hit->ref.type != TYPE_NONE);
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	if (!bvh || !bvh->root)
		return (false);
	hit->t = MAX_VALUE;
	hit->ref.type = TYPE_NONE;
	return (traverse_bvh(bvh, ray, hit));
}
