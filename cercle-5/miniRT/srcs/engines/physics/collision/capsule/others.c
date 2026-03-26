/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:33:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

int	cap_vs_others(t_scene *s, int idx, t_capsule *cap, t_aabb caabb,
		t_contact *c, int count, int max)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	sa = (t_gjk_shape){cap, gjk_support_capsule, cap->phys.center};
	p = idx + 1;
	while (p < s->capsule_count && count < max)
		if (aabb_overlap(caabb, capsule_aabb(&s->capsules[p])))
		{
			sb = (t_gjk_shape){&s->capsules[p], gjk_support_capsule,
				s->capsules[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cap->phys,
					&s->capsules[p].phys, &cap->transform,
					&s->capsules[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->cylinder_count && count < max)
		if (aabb_overlap(caabb, cylinder_aabb(&s->cylinders[p])))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder,
				s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cap->phys,
					&s->cylinders[p].phys, &cap->transform,
					&s->cylinders[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->rect_count && count < max)
		if (aabb_overlap(caabb, rect_aabb(&s->rects[p])))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect,
				s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cap->phys, &s->rects[p].phys,
					&cap->transform, &s->rects[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->tri_count && count < max)
		if (aabb_overlap(caabb, tri_aabb(&s->tris[p])))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri,
				s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cap->phys, &s->tris[p].phys,
					&cap->transform, &s->tris[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->pyramid_count && count < max)
		if (aabb_overlap(caabb, pyramid_aabb(&s->pyramids[p])))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid,
				s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &cap->phys,
					&s->pyramids[p].phys, &cap->transform,
					&s->pyramids[p].transform, &c[count]);
		}
	return (count);
}
