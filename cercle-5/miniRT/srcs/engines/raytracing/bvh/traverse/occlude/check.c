/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	test_child_occ(const t_bvh_node4 *n4, size_t i, const t_ray *ray,
		double max_t)
{
	t_aabb	a;
	double	t[2];

	a.min = vec3(n4->min_x[i], n4->min_y[i], n4->min_z[i]);
	a.max = vec3(n4->max_x[i], n4->max_y[i], n4->max_z[i]);
	if (!aabb_intersect_fast(&a, ray, &t[0], &t[1]))
		return (false);
	if (t[0] < 0.0)
		t[0] = 0.0;
	return (t[0] < max_t);
}

static bool	leaf_occ4(const t_bvh *bvh, const t_ray *ray, double max_t,
		size_t sd[2])
{
	size_t	j;

	j = 0;
	while (j < sd[1])
	{
		if (occlude_primitive(ray, bvh->scene,
				bvh->refs[sd[0] + j], max_t))
			return (true);
		j++;
	}
	return (false);
}

static bool	occ_visit4(const t_bvh *bvh, const t_ray *ray, double max_t,
		t_mbvh_stk *stk)
{
	const t_bvh_node4	*n4;
	size_t				i;
	size_t				sd[2];

	n4 = &bvh->nodes4[stk->st[--stk->top]];
	i = 0;
	while (i < n4->n_children)
	{
		if (!test_child_occ(n4, i, ray, max_t))
		{
			i++;
			continue ;
		}
		if (n4->count[i] > 0)
		{
			sd[0] = n4->child[i];
			sd[1] = n4->count[i];
			if (leaf_occ4(bvh, ray, max_t, sd))
				return (true);
		}
		else if (stk->top < 62)
			stk->st[stk->top++] = n4->child[i];
		i++;
	}
	return (false);
}

bool	bvh_occluded4(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_mbvh_stk	stk;

	if (!bvh || !bvh->nodes4)
		return (bvh_occluded(bvh, ray, max_t));
	stk.top = 0;
	stk.st[stk.top++] = 0;
	while (stk.top > 0)
	{
		if (occ_visit4(bvh, ray, max_t, &stk))
			return (true);
	}
	return (false);
}
