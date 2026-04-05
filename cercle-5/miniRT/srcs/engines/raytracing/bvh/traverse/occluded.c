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

static void	push_occ_children(t_bvh_trav *v, size_t idx, double max_t)
{
	size_t	l;
	double	t[2][2];
	bool	h[2];

	l = v->bvh->nodes[idx].left_or_first;
	h[0] = aabb_intersect_fast(&v->bvh->nodes[l].bbox, v->ray,
			&t[0][0], &t[0][1]);
	h[1] = aabb_intersect_fast(&v->bvh->nodes[idx + 1].bbox, v->ray,
			&t[1][0], &t[1][1]);
	h[0] = h[0] && (t[0][0] < max_t);
	h[1] = h[1] && (t[1][0] < max_t);
	if (h[0] && h[1] && t[0][0] <= t[1][0])
	{
		v->stack[(*v->top)++] = idx + 1;
		v->stack[(*v->top)++] = l;
	}
	else if (h[0] && h[1])
	{
		v->stack[(*v->top)++] = l;
		v->stack[(*v->top)++] = idx + 1;
	}
	else if (h[0])
		v->stack[(*v->top)++] = l;
	else if (h[1])
		v->stack[(*v->top)++] = idx + 1;
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_bvh_trav	v;
	size_t		stack[128];
	size_t		top;
	double		tm[2];

	if (!bvh || !bvh->nodes || !aabb_intersect_fast(&bvh->nodes[0].bbox, ray,
			&tm[0], &tm[1]) || tm[0] >= max_t)
		return (false);
	top = 0;
	stack[top++] = 0;
	v = (t_bvh_trav){stack, NULL, &top, bvh, ray};
	while (top > 0)
	{
		if (bvh->nodes[stack[top - 1]].count > 0)
		{
			if (check_leaf_occlusion(bvh, stack[--top], ray, max_t))
				return (true);
		}
		else if (top < 126)
			push_occ_children(&v, stack[--top], max_t);
		else
			top--;
	}
	return (false);
}
