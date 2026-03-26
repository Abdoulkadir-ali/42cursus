/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

int	rect_vs_others(t_scene *s, int idx, t_rect *rc, t_aabb raabb, t_contact *c, int count, int max)
{
	t_gjk_shape	sa = {rc, gjk_support_rect, rc->phys.center};
	t_gjk_shape	sb;
	int p = idx + 1;
	while (p < s->rect_count && count < max)
		if (aabb_overlap(raabb, rect_aabb(&s->rects[p])))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect, s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &rc->phys, &s->rects[p].phys, &rc->transform, &s->rects[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->tri_count && count < max)
		if (aabb_overlap(raabb, tri_shape_aabb(&s->tris[p])))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri, s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &rc->phys, &s->tris[p].phys, &rc->transform, &s->tris[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->pyramid_count && count < max)
		if (aabb_overlap(raabb, pyramid_aabb(&s->pyramids[p])))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid, s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &rc->phys, &s->pyramids[p].phys, &rc->transform, &s->pyramids[p].transform, &c[count]);
		}
	return (count);
}
