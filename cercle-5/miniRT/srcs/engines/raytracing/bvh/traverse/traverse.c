/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:08:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	process_leaf(const t_bvh *bvh, size_t node_idx, const t_ray *r,
		t_hit *h)
{
	size_t	i;
	t_hit	tmp;

	i = 0;
	while (i < bvh->nodes[node_idx].count)
	{
		tmp.t = h->t;
		if (intersect_object(r, bvh->scene,
				bvh->refs[bvh->nodes[node_idx].left_or_first + i], &tmp))
		{
			if (tmp.t < h->t)
				*h = tmp;
		}
		i++;
	}
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	size_t	stack[64];
	size_t	top;
	size_t	node_idx;
	double	tmin;
	double	tmax;

	if (!bvh || !bvh->nodes)
		return (false);
	top = 0;
	stack[top++] = 0;
	while (top > 0)
	{
		node_idx = stack[--top];
		if (!aabb_intersect_fast(&bvh->nodes[node_idx].bbox, ray, &tmin, &tmax)
			|| tmin >= hit->t)
			continue ;
		if (bvh->nodes[node_idx].count > 0)
			process_leaf(bvh, node_idx, ray, hit);
		else
		{
			stack[top++] = bvh->nodes[node_idx].left_or_first;
			stack[top++] = node_idx + 1;
		}
	}
	return (hit->t < 1e29);
}
