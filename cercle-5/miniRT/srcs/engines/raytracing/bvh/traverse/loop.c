/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:42:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

__attribute__((optimize("O3")))
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

__attribute__((optimize("O3")))
static void	step_trav(t_bvh_trav *v, const t_bvh *bvh,
		const t_ray *ray, t_hit *hit)
{
	size_t	top;
	float	t0;
	size_t	idx;

	top = *v->top - 1;
	t0 = v->stack[top].t;
	idx = v->stack[top].idx;
	*v->top = top;
	if (t0 >= (float)hit->t)
		return ;
	if (bvh->nodes[idx].count > 0)
		process_leaf(bvh, idx, ray, hit);
	else if (top < 124)
		bvh_push_children(v, idx, hit->t);
}

__attribute__((optimize("O3")))
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_bvh_trav		v;
	t_bvh_trav_init	cfg;
	t_stk_entry		stack[128];
	size_t			top;
	double			tmp_tmax;

	cfg.t0 = 0.0;
	if (!bvh || !bvh->nodes || !aabb_intersect_fast(&bvh->nodes[0].bbox, ray,
			&cfg.t0, &tmp_tmax) || (cfg.t0 >= hit->t))
		return (false);
	top = 0;
	cfg.stack = stack;
	cfg.top = &top;
	cfg.bvh = bvh;
	cfg.ray = ray;
	init_trav(&v, &cfg);
	while (top > 0)
		step_trav(&v, bvh, ray, hit);
	return (hit->t < 1e29);
}
