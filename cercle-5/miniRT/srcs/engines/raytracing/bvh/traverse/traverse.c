/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 18:11:51 by abdoali          ###   ########.fr       */
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

static void	push_children(size_t *stack, size_t *top, const t_bvh *bvh,
		double *stk_t, const t_ray *ray, size_t node_idx, double cur_t)
{
	size_t	left;
	size_t	right;
	double	tl;
	double	tl_max;
	double	tr;
	double	tr_max;
	bool	hl;
	bool	hr;

	left = bvh->nodes[node_idx].left_or_first;
	right = node_idx + 1;
	tl = 0.0;
	tr = 0.0;
	hl = aabb_intersect_fast(&bvh->nodes[left].bbox, ray, &tl, &tl_max);
	hr = aabb_intersect_fast(&bvh->nodes[right].bbox, ray, &tr, &tr_max);
	if (tl < 0.0)
		tl = 0.0;
	if (tr < 0.0)
		tr = 0.0;
	if (hl && tl >= cur_t)
		hl = false;
	if (hr && tr >= cur_t)
		hr = false;
	if (hl && hr)
	{
		if (tl <= tr)
		{
			stack[(*top)] = right; stk_t[(*top)++] = tr;
			stack[(*top)] = left;  stk_t[(*top)++] = tl;
		}
		else
		{
			stack[(*top)] = left;  stk_t[(*top)++] = tl;
			stack[(*top)] = right; stk_t[(*top)++] = tr;
		}
	}
	else if (hl)
	{
		stack[(*top)] = left;
		stk_t[(*top)++] = tl;
	}
	else if (hr)
	{
		stack[(*top)] = right;
		stk_t[(*top)++] = tr;
	}
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	size_t	stack[128];
	double	stk_t[128];
	size_t	top;
	size_t	node_idx;
	double	tmin;
	double	tmax;

	if (!bvh || !bvh->nodes)
		return (false);
	tmin = 0.0;
	tmax = hit->t;
	if (!aabb_intersect_fast(&bvh->nodes[0].bbox, ray, &tmin, &tmax))
		return (false);
	if (tmin < 0.0)
		tmin = 0.0;
	if (tmin >= hit->t)
		return (false);
	top = 0;
	stack[top] = 0;
	stk_t[top++] = tmin;
	while (top > 0)
	{
		node_idx = stack[--top];
		tmin = stk_t[top];
		if (tmin >= hit->t)
			continue ;
		if (bvh->nodes[node_idx].count > 0)
			process_leaf(bvh, node_idx, ray, hit);
		else if (top < 124)
			push_children(stack, &top, bvh, stk_t, ray, node_idx, hit->t);
	}
	return (hit->t < 1e29);
}
