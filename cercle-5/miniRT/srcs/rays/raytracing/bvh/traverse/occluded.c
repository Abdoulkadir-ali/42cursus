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

static bool	process_leaf_occluded(const t_bvh *bvh, int node_idx,
			const t_ray *ray, double max_t)
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
		if (bvh->refs[i].type == TYPE_MESH)
		{
			if (mesh_occluded(ray, &bvh->scene->meshes[bvh->refs[i].index],
					max_t))
				return (true);
		}
		else if (bvh->refs[i].type == TYPE_ANIM)
		{
			if (mesh_occluded(ray,
					&bvh->scene->animated[bvh->refs[i].index].base, max_t))
				return (true);
		}
		else if (intersect_object(ray, bvh->scene, bvh->refs[i], &temp)
			&& temp.t > EPSILON && temp.t < max_t)
			return (true);
		i++;
	}
	return (false);
}

static bool	traverse_bvh_occluded(const t_bvh *bvh, const t_ray *ray,
		double max_t)
{
	int					stack[128];
	int					ptr;
	int					i;
	const t_bvh_node	*node;
	double				tmin;
	double				tmax;

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
		if (tmin > max_t)
			continue ;
		if (node->count > 0)
		{
			if (process_leaf_occluded(bvh, i, ray, max_t))
				return (true);
		}
		else if (ptr < 126)
		{
			stack[ptr++] = node->left_or_first;
			stack[ptr++] = i + 1;
		}
	}
	return (false);
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	if (!bvh || bvh->num_nodes == 0)
		return (false);
	return (traverse_bvh_occluded(bvh, ray, max_t));
}
