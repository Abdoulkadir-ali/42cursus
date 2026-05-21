/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:21:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	occlude_leaf(t_occ *o, const t_bvh_node *n)
{
	t_hit	h;
	size_t	idx;
	size_t	i;

	i = 0;
	while (i < n->count)
	{
		idx = o->bvh->indices[n->first + i];
		h.t = o->max_t;
		if (hit_one(&o->objs[idx], o->r, &h))
			return (true);
		i++;
	}
	return (false);
}

static int	check_node(t_occ *o, const t_bvh_node *n)
{
	t_hit	h;

	if (n->simd_idx >= 0)
	{
		h.t = o->max_t;
		if (hit_triangle_sse(&o->bvh->soa_tris[n->simd_idx], o->r, &h))
			return (1);
	}
	else if (n->count > 0 && occlude_leaf(o, n))
		return (1);
	return (0);
}

static int	occlude_loop(t_occ *o, size_t *stack, size_t sp, t_vec3 inv_d)
{
	const t_bvh_node	*n;

	while (sp > 0)
	{
		n = &o->bvh->nodes[stack[--sp]];
		if (!aabb_hit(&n->box, o->r, inv_d, o->max_t))
			continue ;
		if (check_node(o, n))
			return (1);
		if (n->count == 0 && sp + 2 <= o->bvh->n_nodes)
		{
			stack[sp++] = n->first;
			stack[sp++] = n->first + 1;
		}
	}
	return (0);
}

int	bvh_occluded(const t_bvh *bvh, const t_ray *r, float max_t,
		const t_object *objs)
{
	size_t	*stack;
	t_occ	o;
	t_vec3	inv_d;
	int		res;

	if (bvh->n_nodes > 0)
		stack = malloc(sizeof(size_t) * bvh->n_nodes);
	else
		stack = malloc(sizeof(size_t) * 1);
	if (!stack || bvh->n_nodes == 0)
		return (free(stack), 0);
	o = (t_occ){bvh, r, objs, max_t};
	inv_d = v3(1.0f / r->d.x, 1.0f / r->d.y, 1.0f / r->d.z);
	stack[0] = 0;
	res = occlude_loop(&o, stack, 1, inv_d);
	free(stack);
	return (res);
}
