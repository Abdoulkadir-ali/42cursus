/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

static int	cyl_vs_others(t_scene *s, int idx, t_cylinder *cy, t_aabb cyaabb, t_contact *c, int count, int max)
{
	t_gjk_shape sa = {cy, gjk_support_cylinder, cy->phys.center};
	t_gjk_shape sb;
	int p = idx + 1;
	while (p < s->cylinder_count && count < max)
		if (aabb_overlap(cyaabb, cylinder_aabb(&s->cylinders[p])))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder, s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cy->phys, &s->cylinders[p].phys, &cy->transform, &s->cylinders[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->rect_count && count < max)
		if (aabb_overlap(cyaabb, rect_aabb(&s->rects[p])))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect, s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cy->phys, &s->rects[p].phys, &cy->transform, &s->rects[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->tri_count && count < max)
		if (aabb_overlap(cyaabb, tri_shape_aabb(&s->tris[p])))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri, s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cy->phys, &s->tris[p].phys, &cy->transform, &s->tris[p].xform, &c[count]);
		}
	p = -1;
	while (++p < s->pyramid_count && count < max)
		if (aabb_overlap(cyaabb, pyramid_aabb(&s->pyramids[p])))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid, s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cy->phys, &s->pyramids[p].phys, &cy->transform, &s->pyramids[p].transform, &c[count]);
		}
	return (count);
}

int	query_cylinder(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_cylinder	*cy = &s->cylinders[idx];
	t_aabb		cyaabb;
	t_gjk_shape	sa;

	if (cy->phys.is_static) return (count);
	cyaabb = cylinder_aabb(cy);
	sa = (t_gjk_shape){cy, gjk_support_cylinder, cy->phys.center};
	count = gjk_vs_all_planes(&sa, &cy->phys, &cy->transform, s, c, count, max);
	return (cyl_vs_others(s, idx, cy, cyaabb, c, count, max));
}
