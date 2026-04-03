/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:19:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:19:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	occlude_primitive(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
		double max_t)
{
	t_hit	h;

	h.t = max_t;
	if (intersect_object(ray, sc, ref, &h))
		return (h.t < max_t);
	return (false);
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
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
			|| tmin >= max_t)
			continue ;
		if (bvh->nodes[node_idx].count > 0)
		{
			size_t i = 0;
			while (i < bvh->nodes[node_idx].count)
			{
				if (occlude_primitive(ray, bvh->scene,
						bvh->refs[bvh->nodes[node_idx].left_or_first + i], max_t))
					return (true);
				i++;
			}
		}
		else
		{
			stack[top++] = bvh->nodes[node_idx].left_or_first + 1;
			stack[top++] = bvh->nodes[node_idx].left_or_first;
		}
	}
	return (false);
}
