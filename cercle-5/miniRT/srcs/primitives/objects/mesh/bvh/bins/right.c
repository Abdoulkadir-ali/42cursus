/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:14:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:56:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static void	bvh_update_best(t_bvh_split *s, size_t axis, size_t c)
{
	double	cost;

	if (c == 0 || s->right_count == 0)
		return ;
	cost = 1.0 + (s->left_area[s->i - 1] / s->parent_sa) * c
		+ (aabb_surface_area(s->right_box) / s->parent_sa) * s->right_count;
	if (cost >= s->best_cost)
		return ;
	s->best_cost = cost;
	s->best_axis = init_index(axis, false);
	s->split_pos = s->min_val + (s->i * (s->max_val - s->min_val)) / BVH_BINS;
}

/**
 * Sweeps from right to left along bins to calculate final SAH costs 
 * and identify the optimal split position.
 */
void	bvh_sweep_right(t_bvh_split *s, size_t axis)
{
	size_t	c;

	s->right_box = aabb_create_empty();
	s->right_count = 0;
	s->i = BVH_BINS - 1;
	while (s->i > 0)
	{
		s->right_count += s->bins[s->i].count;
		s->right_box = aabb_union(&s->right_box, &s->bins[s->i].bounds);
		c = s->left_counts[s->i - 1];
		bvh_update_best(s, axis, c);
		s->i--;
	}
}
