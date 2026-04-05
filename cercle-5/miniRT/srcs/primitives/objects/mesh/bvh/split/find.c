/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static void	init_find(t_bvh_find *f, t_bvh_eval *eval)
{
	bvh_centroid_bounds(f->bvh, f->first, f->count, &f->s.centroid_bounds);
	f->s.best_axis = -1;
	f->s.best_cost = (double)f->count * 2.0;
	f->s.split_pos = 0;
	eval->bvh = f->bvh;
	eval->node = f->node;
	eval->first = f->first;
	eval->count = f->count;
	eval->s = &f->s;
	eval->axis = 0;
}

/**
 * Finds the optimal split plane for a BVH node by evaluating all three 
 * axes (X, Y, Z) and selecting the one with the lowest SAH cost.
 */
bool	bvh_find_split(t_bvh_find *f)
{
	t_bvh_eval	eval;

	init_find(f, &eval);
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
