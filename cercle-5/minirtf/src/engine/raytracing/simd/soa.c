/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:53:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	fill_soa(t_tri_soa4 *s, size_t i, const t_triangle *t, size_t id)
{
	s->ax.v[i] = t->a.x;
	s->ay.v[i] = t->a.y;
	s->az.v[i] = t->a.z;
	s->e1x.v[i] = t->b.x - t->a.x;
	s->e1y.v[i] = t->b.y - t->a.y;
	s->e1z.v[i] = t->b.z - t->a.z;
	s->e2x.v[i] = t->c.x - t->a.x;
	s->e2y.v[i] = t->c.y - t->a.y;
	s->e2z.v[i] = t->c.z - t->a.z;
	s->nx.v[i] = t->n.x;
	s->ny.v[i] = t->n.y;
	s->nz.v[i] = t->n.z;
	s->ids[i] = (int)id;
}

static void	pad_soa(t_tri_soa4 *s, size_t i)
{
	s->ax.v[i] = 0.0f;
	s->ay.v[i] = 0.0f;
	s->az.v[i] = 0.0f;
	s->e1x.v[i] = 0.0f;
	s->e1y.v[i] = 0.0f;
	s->e1z.v[i] = 0.0f;
	s->e2x.v[i] = 0.0f;
	s->e2y.v[i] = 0.0f;
	s->e2z.v[i] = 0.0f;
	s->nx.v[i] = 0.0f;
	s->ny.v[i] = 1.0f;
	s->nz.v[i] = 0.0f;
	s->ids[i] = 0x7fffffff;
}

void	assign_node_soa(t_bvh *bvh, const t_object *objs, t_bvh_node *node)
{
	size_t	k;
	size_t	j;
	size_t	idx;

	k = bvh->n_soa++;
	j = 0;
	while (j < 4)
	{
		if (j < node->count)
		{
			idx = bvh->indices[node->first + j];
			fill_soa(&bvh->soa_tris[k], j, &objs[idx].u.tri, idx);
		}
		else
			pad_soa(&bvh->soa_tris[k], j);
		j++;
	}
	node->simd_idx = k;
}
