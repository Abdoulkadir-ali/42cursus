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

static bool	traverse_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	int					stack[128];
	int					ptr;
	int					i;
	const t_bvh_node	*node;
	double				tmin;
	double				tmax;
	int					left;
	int					right;
	double				tmin_l;
	double				tmax_l;
	double				tmin_r;
	double				tmax_r;
	bool				hit_l;
	bool				hit_r;

	ptr = 0;
	stack[ptr++] = 0;
	while (ptr > 0)
	{
		i = stack[--ptr];
		node = &bvh->nodes[i];
		if (!aabb_intersect_fast(&node->bbox, ray, &tmin, &tmax))
			continue ;
		if (tmin < 0.0)
			tmin = 0.0;
		if (tmin > hit->t)
			continue ;
		if (node->count > 0)
			process_leaf_flat(bvh, i, ray, hit);
		else if (ptr < 124)
		{
			left = node->left_or_first;
			right = i + 1;
			hit_l = aabb_intersect_fast(&bvh->nodes[left].bbox,
					ray, &tmin_l, &tmax_l);
			hit_r = aabb_intersect_fast(&bvh->nodes[right].bbox,
					ray, &tmin_r, &tmax_r);
			if (hit_l && hit_r)
			{
				if (tmin_l <= tmin_r)
				{
					stack[ptr++] = right;
					stack[ptr++] = left;
				}
				else
				{
					stack[ptr++] = left;
					stack[ptr++] = right;
				}
			}
			else if (hit_l)
				stack[ptr++] = left;
			else if (hit_r)
				stack[ptr++] = right;
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
