/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 10:13:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	push_to_trav(t_bvh_trav *v, size_t idx, double t)
{
	v->stack[*v->top] = idx;
	v->stk_t[(*v->top)++] = t;
}

static void	push_sort(t_bvh_trav *v, double t[2], size_t l, size_t r)
{
	if (t[0] <= t[1])
	{
		push_to_trav(v, r, t[1]);
		push_to_trav(v, l, t[0]);
	}
	else
	{
		push_to_trav(v, l, t[0]);
		push_to_trav(v, r, t[1]);
	}
}

static double	clamp0(double t)
{
	if (t < 0.0)
		return (0.0);
	return (t);
}

void	bvh_trav_push0(t_bvh_trav *v, t_bvh_trav_init *cfg)
{
	v->stack = cfg->stack;
	v->stk_t = cfg->stk_t;
	v->top = cfg->top;
	v->bvh = cfg->bvh;
	v->ray = cfg->ray;
	v->stack[*cfg->top] = 0;
	if (cfg->t0 < 0.0)
		v->stk_t[(*cfg->top)++] = 0.0;
	else
		v->stk_t[(*cfg->top)++] = cfg->t0;
}

void	bvh_push_children(t_bvh_trav *v, size_t idx, double cur_t)
{
	size_t	l;
	double	t[2][2];
	bool	hit[2];

	l = v->bvh->nodes[idx].left_or_first;
	hit[0] = aabb_intersect_fast(&v->bvh->nodes[l].bbox, v->ray,
			&t[0][0], &t[0][1]);
	hit[1] = aabb_intersect_fast(&v->bvh->nodes[idx + 1].bbox, v->ray,
			&t[1][0], &t[1][1]);
	hit[0] = hit[0] && (t[0][0] < cur_t);
	hit[1] = hit[1] && (t[1][0] < cur_t);
	if (hit[0] && hit[1])
		push_sort(v, (double [2]){clamp0(t[0][0]), clamp0(t[1][0])},
			l, idx + 1);
	else if (hit[0])
		push_to_trav(v, l, clamp0(t[0][0]));
	else if (hit[1])
		push_to_trav(v, idx + 1, clamp0(t[1][0]));
}
