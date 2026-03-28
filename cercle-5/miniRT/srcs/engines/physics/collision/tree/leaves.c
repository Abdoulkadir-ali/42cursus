/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:48:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_aabb	fatten(t_aabb a)
{
	t_aabb	r;

	r.min[0] = a.min[0] - DBVT_FAT_MARGIN;
	r.min[1] = a.min[1] - DBVT_FAT_MARGIN;
	r.min[2] = a.min[2] - DBVT_FAT_MARGIN;
	r.max[0] = a.max[0] + DBVT_FAT_MARGIN;
	r.max[1] = a.max[1] + DBVT_FAT_MARGIN;
	r.max[2] = a.max[2] + DBVT_FAT_MARGIN;
	return (r);
}

static void	compute_prim_aabb(t_primitive_array *p, int i)
{
	float	r = p->radii[i];
	float	h = p->heights[i];
	float	ex = p->ex[i], ey = p->ey[i], ez = p->ez[i];

	if (p->types[i] == PRIM_SPHERE)
	{
		p->abb_min_x[i] = p->px[i] - r; p->abb_min_y[i] = p->py[i] - r; p->abb_min_z[i] = p->pz[i] - r;
		p->abb_max_x[i] = p->px[i] + r; p->abb_max_y[i] = p->py[i] + r; p->abb_max_z[i] = p->pz[i] + r;
	}
	else if (p->types[i] == PRIM_BOX || p->types[i] == PRIM_RECT)
	{
		p->abb_min_x[i] = p->px[i] - ex; p->abb_min_y[i] = p->py[i] - ey; p->abb_min_z[i] = p->pz[i] - ez;
		p->abb_max_x[i] = p->px[i] + ex; p->abb_max_y[i] = p->py[i] + ey; p->abb_max_z[i] = p->pz[i] + ez;
	}
	else /* Generic fallback - larger radius */
	{
		float m = (r > h) ? r : h;
		p->abb_min_x[i] = p->px[i] - m; p->abb_min_y[i] = p->py[i] - m; p->abb_min_z[i] = p->pz[i] - m;
		p->abb_max_x[i] = p->px[i] + m; p->abb_max_y[i] = p->py[i] + m; p->abb_max_z[i] = p->pz[i] + m;
	}
}

static void	push_leaf(t_dbvt *t, int idx, t_aabb aabb, t_phys_type type)
{
	t_dbvt_leaf	*l;

	if (t->leaf_count >= DBVT_MAX_LEAVES)
		return ;
	l = &t->leaves[t->leaf_count++];
	l->prim_idx = idx;
	l->fat_aabb = fatten(aabb);
	l->type = type;
}

void	collect_leaves(t_physics *phys, t_dbvt *t)
{
	size_t				i;
	t_primitive_array	*p = &phys->scene->primitives;

	t->leaf_count = 0;
	i = 0;
	while (i < p->count)
	{
		if (p->has_phys[i] && !p->is_static[i])
		{
			t_aabb a;
			compute_prim_aabb(p, (int)i);
			a.min[0] = p->abb_min_x[i];
			a.min[1] = p->abb_min_y[i];
			a.min[2] = p->abb_min_z[i];
			a.max[0] = p->abb_max_x[i];
			a.max[1] = p->abb_max_y[i];
			a.max[2] = p->abb_max_z[i];
			push_leaf(t, (int)i, a, (t_phys_type)p->types[i]);
		}
		i++;
	}
}
