/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:19:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:47:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	occlude_primitive(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
		double max_t)
{
	t_hit	h;

	h.t = max_t;
	if (intersect_object(ray, sc, ref, &h))
		return (h.t < max_t);
	return (false);
}

static bool	check_leaf_occlusion(const t_bvh *bvh, size_t node_idx,
		const t_ray *ray, double max_t)
{
	size_t	i;
	size_t	ref_start;

	i = 0;
	ref_start = bvh->nodes[node_idx].left_or_first;
	while (i < bvh->nodes[node_idx].count)
	{
		if (occlude_primitive(ray, bvh->scene, bvh->refs[ref_start + i], max_t))
			return (true);
		i++;
	}
	return (false);
}

static bool	traverse_step(const t_bvh *bvh, const t_ray *ray, double max_t,
		size_t *stack)
{
	size_t	top;
	size_t	node_idx;
	double	t[2];

	top = 0;
	stack[++top] = 0;
	while (top > 0)
	{
		node_idx = stack[top--];
		if (!aabb_intersect_fast(&bvh->nodes[node_idx].bbox, ray, &t[0], &t[1])
			|| t[0] >= max_t)
			continue ;
		if (bvh->nodes[node_idx].count > 0)
		{
			if (check_leaf_occlusion(bvh, node_idx, ray, max_t))
				return (true);
		}
		else
		{
			stack[++top] = bvh->nodes[node_idx].left_or_first + 1;
			stack[++top] = bvh->nodes[node_idx].left_or_first;
		}
	}
	return (false);
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	size_t	stack[128];

	if (!bvh || !bvh->nodes)
		return (false);
	return (traverse_step(bvh, ray, max_t, stack));
}
