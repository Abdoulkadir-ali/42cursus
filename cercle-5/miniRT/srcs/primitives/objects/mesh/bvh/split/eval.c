/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Evaluates the Surface Area Heuristic (SAH) cost for splitting a BVH node 
 * along a specific axis. It initializes bins, performs sweeps, and identifies 
 * the best split within this axis.
 */
void	bvh_eval_axis(t_bvh_eval *e)
{
	t_bvh_bins	bins;
	double			min_val;
	double			max_val;

	bvh_axis_min_max(&e->s->centroid_bounds, e->axis, &min_val, &max_val);
	e->s->min_val = min_val;
	e->s->max_val = max_val;
	if (e->s->max_val - e->s->min_val < 1e-5)
		return ;
	bvh_bins_init(e->s->bins);
	e->s->scale = BVH_BINS / ((e->s->max_val - e->s->min_val) + 1e-9);
	bins.bvh = e->bvh;
	bins.first = e->first;
	bins.count = e->count;
	bins.axis = e->axis;
	bins.min_val = e->s->min_val;
	bins.scale = e->s->scale;
	bins.bins = e->s->bins;
	bvh_fill_bins(&bins);
	e->s->parent_sa = aabb_surface_area(e->node->bbox);
	bvh_sweep_left(e->s->bins, e->s->left_area, e->s->left_counts);
	bvh_sweep_right(e->s, e->axis);
}
