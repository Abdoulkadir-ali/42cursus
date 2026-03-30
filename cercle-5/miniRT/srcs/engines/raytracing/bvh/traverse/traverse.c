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

static void	process_leaf_flat(const t_bvh *bvh, int node_idx,
			const t_ray *ray, t_hit *hit)
{
	const t_bvh_node	*node;
	t_hit				temp;
	int					i;
	int					end;

	node = &bvh->nodes[node_idx];
	i = node->left_or_first;
	end = i + node->count;
	while (i < end)
	{
		temp.t = MAX_VALUE;
		temp.ref.type = TYPE_NONE;
		if (intersect_object(ray, bvh->scene, bvh->refs[i], &temp)
			&& temp.t < hit->t)
			*hit = temp;
		i++;
	}
}

/*
** Optimized BVH traversal using a compact stack and interleaved
** AABB tests. Pruning is done before every child push.
*/
static bool	traverse_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	int					stack[64];
	double				stack_tmin[64];
	int					ptr;
	int					i;
	const t_bvh_node	*node;
	double				tmin;
	double				tmax;

	if (!aabb_intersect_fast(&bvh->nodes[0].bbox, ray, &tmin, &tmax)
		|| tmin > hit->t)
		return (false);
	ptr = 0;
	stack[ptr] = 0;
	stack_tmin[ptr] = tmin;
	ptr++;
	while (ptr > 0)
	{
		i = stack[--ptr];
		if (stack_tmin[ptr] > hit->t)
			continue ;
		node = &bvh->nodes[i];
		if (node->count > 0)
			process_leaf_flat(bvh, i, ray, hit);
		else
		{
			int left = node->left_or_first;
			int right = i + 1;
			double tl, tl_max, tr, tr_max;
			bool hit_l = aabb_intersect_fast(&bvh->nodes[left].bbox, ray, &tl, &tl_max);
			bool hit_r = aabb_intersect_fast(&bvh->nodes[right].bbox, ray, &tr, &tr_max);
			
			if (tl < 0.0) tl = 0.0;
			if (tr < 0.0) tr = 0.0;
			if (hit_l && tl > hit->t) hit_l = false;
			if (hit_r && tr > hit->t) hit_r = false;

			if (hit_l && hit_r)
			{
				if (tl <= tr)
				{
					stack[ptr] = right; stack_tmin[ptr] = tr; ptr++;
					stack[ptr] = left;  stack_tmin[ptr] = tl; ptr++;
				}
				else
				{
					stack[ptr] = left;  stack_tmin[ptr] = tl; ptr++;
					stack[ptr] = right; stack_tmin[ptr] = tr; ptr++;
				}
			}
			else if (hit_l)
			{
				stack[ptr] = left; stack_tmin[ptr] = tl; ptr++;
			}
			else if (hit_r)
			{
				stack[ptr] = right; stack_tmin[ptr] = tr; ptr++;
			}
		}
	}
	return (hit->ref.type != TYPE_NONE);
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	if (!bvh || bvh->num_nodes == 0)
		return (false);
	hit->t = MAX_VALUE;
	hit->ref.type = TYPE_NONE;
	return (traverse_bvh(bvh, ray, hit));
}
