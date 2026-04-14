/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 10:13:32 by abdoali          ###   ########.fr       */
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

static void	init_trav(t_bvh_trav *v, t_bvh_trav_init *cfg)
{
	bvh_trav_push0(v, cfg);
}

static void	step_trav(t_bvh_trav *v, const t_bvh *bvh,
		const t_ray *ray, t_hit *hit)
{
	size_t	top;
	double	t0;

	top = *v->top - 1;
	t0 = v->stk_t[top];
	*v->top = top;
	if (t0 >= hit->t)
		return ;
	if (bvh->nodes[v->stack[top]].count > 0)
		process_leaf(bvh, v->stack[top], ray, hit);
	else if (top < 124)
		bvh_push_children(v, v->stack[top], hit->t);
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_bvh_trav		v;
	t_bvh_trav_init	cfg;
	size_t			stack[128];
	double			stk_t[128];
	size_t			top;

	cfg.t0 = 0.0;
	if (!bvh || !bvh->nodes || !aabb_intersect_fast(&bvh->nodes[0].bbox, ray,
			&cfg.t0, &stk_t[0]) || (cfg.t0 >= hit->t))
		return (false);
	top = 0;
	cfg.stack = stack;
	cfg.stk_t = stk_t;
	cfg.top = &top;
	cfg.bvh = bvh;
	cfg.ray = ray;
	init_trav(&v, &cfg);
	while (top > 0)
		step_trav(&v, bvh, ray, hit);
	return (hit->t < 1e29);
}
