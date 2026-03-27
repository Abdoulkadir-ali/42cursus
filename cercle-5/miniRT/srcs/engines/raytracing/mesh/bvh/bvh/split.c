/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	bvh_eval_axis(t_bvh_eval_ctx *e)
{
	t_bvh_bins_ctx	bins;
	double			min_val;
	double			max_val;

	bvh_axis_min_max(&e->s->centroid_bounds, e->axis, &min_val, &max_val);
	e->s->min_val = min_val;
	e->s->max_val = max_val;
	if (e->s->max_val - e->s->min_val < 1e-5)
		return ;
	bvh_bins_init(e->s->bins);
	e->s->scale = BVH_BINS / ((e->s->max_val - e->s->min_val) + 1e-9);
	bins.ctx = e->ctx;
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

bool	bvh_find_split(t_bvh_find_ctx *f)
{
	t_bvh_eval_ctx	eval;

	bvh_centroid_bounds(f->ctx, f->first, f->count, &f->s.centroid_bounds);
	f->s.best_axis = -1;
	f->s.best_cost = (double)f->count;
	f->s.split_pos = 0;
	eval.ctx = f->ctx;
	eval.node = f->node;
	eval.first = f->first;
	eval.count = f->count;
	eval.s = &f->s;
	eval.axis = 0;
	while (eval.axis < 3)
	{
		bvh_eval_axis(&eval);
		eval.axis++;
	}
	if (f->s.best_axis == -1)
		return (false);
	f->out->axis = f->s.best_axis;
	f->out->pos = f->s.split_pos;
	return (true);
}
