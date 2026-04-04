/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:19:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	check_leaf_occlusion(const t_bvh *bvh, size_t node_idx,
		const t_ray *ray, double max_t)
{
	size_t	i;
	size_t	ref_start;

	i = 0;
	ref_start = bvh->nodes[node_idx].left_or_first;
	while (i < bvh->nodes[node_idx].count)
	{
		if (occlude_primitive(ray, bvh->scene, bvh->refs[ref_start + i],
				max_t))
			return (true);
		i++;
	}
	return (false);
}

static void	push_occ_children(size_t *stack, size_t *top, const t_bvh *bvh,
		const t_ray *ray, size_t node_idx, double max_t)
{
	size_t	left;
	size_t	right;
	double	tl;
	double	tl_max;
	double	tr;
	double	tr_max;
	bool	hl;
	bool	hr;

	left = bvh->nodes[node_idx].left_or_first;
	right = node_idx + 1;
	tl = 0.0;
	tr = 0.0;
	hl = aabb_intersect_fast(&bvh->nodes[left].bbox, ray, &tl, &tl_max);
	hr = aabb_intersect_fast(&bvh->nodes[right].bbox, ray, &tr, &tr_max);
	if (tl < 0.0)
		tl = 0.0;
	if (tr < 0.0)
		tr = 0.0;
	if (hl && tl >= max_t)
		hl = false;
	if (hr && tr >= max_t)
		hr = false;
	if (hl && hr)
	{
		if (tl <= tr)
		{
			stack[(*top)++] = right;
			stack[(*top)++] = left;
		}
		else
		{
			stack[(*top)++] = left;
			stack[(*top)++] = right;
		}
	}
	else if (hl)
		stack[(*top)++] = left;
	else if (hr)
		stack[(*top)++] = right;
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	size_t	stack[128];
	size_t	top;
	size_t	node_idx;
	double	tmin;
	double	tmax;

	if (!bvh || !bvh->nodes)
		return (false);
	tmin = 0.0;
	tmax = max_t;
	if (!aabb_intersect_fast(&bvh->nodes[0].bbox, ray, &tmin, &tmax))
		return (false);
	if (tmin < 0.0)
		tmin = 0.0;
	if (tmin >= max_t)
		return (false);
	top = 0;
	stack[top++] = 0;
	while (top > 0)
	{
		node_idx = stack[--top];
		if (bvh->nodes[node_idx].count > 0)
		{
			if (check_leaf_occlusion(bvh, node_idx, ray, max_t))
				return (true);
		}
		else if (top < 126)
			push_occ_children(stack, &top, bvh, ray, node_idx, max_t);
	}
	return (false);
}
