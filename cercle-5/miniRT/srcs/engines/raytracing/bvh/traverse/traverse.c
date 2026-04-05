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

static void	push_children(t_bvh_trav *v, size_t idx, double cur_t)
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
		push_sort(v, (double [2]){fmax(0, t[0][0]), fmax(0, t[1][0])},
			l, idx + 1);
	else if (hit[0])
		push_to_trav(v, l, fmax(0, t[0][0]));
	else if (hit[1])
		push_to_trav(v, idx + 1, fmax(0, t[1][0]));
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_bvh_trav	v;
	size_t		stack[128];
	double		stk_t[128];
	size_t		top;
	double		tm[2];

	if (!bvh || !bvh->nodes || !aabb_intersect_fast(&bvh->nodes[0].bbox, ray,
			&tm[0], &tm[1]) || (tm[0] >= hit->t))
		return (false);
	top = 0;
	v = (t_bvh_trav){stack, stk_t, &top, bvh, ray};
	push_to_trav(&v, 0, fmax(0.0, tm[0]));
	while (top > 0)
	{
		tm[0] = stk_t[--top];
		if (tm[0] < hit->t)
		{
			if (bvh->nodes[stack[top]].count > 0)
				process_leaf(bvh, stack[top], ray, hit);
			else if (top < 124)
				push_children(&v, stack[top], hit->t);
		}
	}
	return (hit->t < 1e29);
}
