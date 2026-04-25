/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:19:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:44:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

__attribute__((optimize("O3")))
static bool	check_leaf_occlusion(const t_bvh *bvh, size_t node_idx,
		const t_ray *ray, double max_t)
{
	size_t	i;

	i = 0;
	while (i < bvh->nodes[node_idx].count)
	{
		if (occlude_primitive(ray, bvh->scene,
				bvh->refs[bvh->nodes[node_idx].left_or_first + i], max_t))
			return (true);
		i++;
	}
	return (false);
}

__attribute__((optimize("O3")))
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_stk_entry	stack[128];
	size_t		top;
	t_bvh_trav	v;
	size_t		idx;
	double		t0;
	double		t_max;

	if (!bvh || !bvh->nodes)
		return (false);
	t0 = 0.0;
	if (!aabb_intersect_fast(&bvh->nodes[0].bbox, ray, &t0, &t_max) || t0 >= max_t)
		return (false);
	top = 0;
	stack[top].idx = 0;
	stack[top++].t = (float)t0;
	v = (t_bvh_trav){stack, &top, bvh, ray};
	while (top > 0)
	{
		idx = stack[top - 1].idx;
		if (stack[--top].t >= (float)max_t)
			continue ;
		if (bvh->nodes[idx].count > 0)
		{
			if (check_leaf_occlusion(bvh, idx, ray, max_t))
				return (true);
		}
		else if (top < 126)
			bvh_push_children(&v, idx, max_t);
	}
	return (false);
}
