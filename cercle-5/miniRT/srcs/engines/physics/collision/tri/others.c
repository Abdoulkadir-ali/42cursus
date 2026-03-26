/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:32:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

int	tri_vs_others(t_scene *s, int idx, t_tri_shape *tr, t_aabb taabb,
		t_contact *c, int count, int max)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	p = idx;
	sa = (t_gjk_shape){tr, gjk_support_tri, tr->phys.center};
	while (++p < s->tri_count && count < max)
		if (aabb_overlap(taabb, tri_aabb(&s->tris[p])))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &tr->phys, &s->tris[p].phys,
					&tr->transform, &s->tris[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->pyramid_count && count < max)
		if (aabb_overlap(taabb, pyramid_aabb(&s->pyramids[p])))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &tr->phys, &s->pyramids[p].phys,
					&tr->transform, &s->pyramids[p].transform, &c[count]);
		}
	return (count);
}
