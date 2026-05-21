/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:21:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	process_leaf(t_trav *t, const t_bvh_node *n)
{
	bool	any;
	size_t	idx;
	size_t	i;

	any = false;
	i = 0;
	while (i < n->count)
	{
		idx = t->bvh->indices[n->first + i];
		if (hit_one(&t->objs[idx], t->r, t->out))
		{
			t->out->obj_index = (int)idx;
			t->out->color = t->objs[idx].color;
			any = true;
		}
		i++;
	}
	return (any);
}

static bool	check_node(t_trav *t, const t_bvh_node *n)
{
	if (n->simd_idx >= 0
		&& hit_triangle_sse(&t->bvh->soa_tris[n->simd_idx], t->r, t->out))
	{
		t->out->color = t->objs[t->out->obj_index].color;
		return (true);
	}
	if (n->count > 0)
		return (process_leaf(t, n));
	return (false);
}

static size_t	*alloc_stack(const t_bvh *bvh)
{
	if (bvh->n_nodes > 0)
		return (malloc(sizeof(size_t) * bvh->n_nodes));
	return (malloc(sizeof(size_t) * 1));
}

static bool	traverse_loop(t_trav *t, size_t *stack)
{
	size_t				sp;
	t_vec3				inv_d;
	const t_bvh_node	*n;
	bool				any_hit;

	inv_d = v3(1.0f / t->r->d.x, 1.0f / t->r->d.y, 1.0f / t->r->d.z);
	stack[0] = 0;
	sp = 1;
	any_hit = false;
	while (sp > 0)
	{
		n = &t->bvh->nodes[stack[--sp]];
		if (!aabb_hit(&n->box, t->r, inv_d, t->out->t))
			continue ;
		any_hit |= check_node(t, n);
		if (n->count == 0 && sp + 2 <= t->bvh->n_nodes)
		{
			stack[sp++] = n->first;
			stack[sp++] = n->first + 1;
		}
	}
	return (any_hit);
}

int	bvh_traverse(const t_bvh *bvh, const t_ray *r, t_hit *out,
		const t_object *objs)
{
	size_t	*stack;
	t_trav	t;
	bool	any_hit;

	stack = alloc_stack(bvh);
	if (!stack || bvh->n_nodes == 0)
		return (free(stack), 0);
	t = (t_trav){bvh, r, objs, out};
	any_hit = traverse_loop(&t, stack);
	return (free(stack), any_hit);
}
