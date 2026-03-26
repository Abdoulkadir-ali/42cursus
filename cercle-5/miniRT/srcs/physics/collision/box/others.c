/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

int	box_vs_others(t_scene *s, int idx, t_box *bx, t_aabb baabb, t_contact *c, int count, int max)
{
	t_gjk_shape sa = {bx, gjk_support_box, bx->phys.center};
	t_gjk_shape sb;
	int p = idx + 1;
	while (p < s->box_count && count < max)
		if (aabb_overlap(baabb, box_aabb(&s->boxes[p])))
		{
			sb = (t_gjk_shape){&s->boxes[p], gjk_support_box, s->boxes[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &bx->phys, &s->boxes[p].phys, &bx->transform, &s->boxes[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->capsule_count && count < max)
		if (aabb_overlap(baabb, capsule_aabb(&s->capsules[p])))
		{
			sb = (t_gjk_shape){&s->capsules[p], gjk_support_capsule, s->capsules[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &bx->phys, &s->capsules[p].phys, &bx->transform, &s->capsules[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->cylinder_count && count < max)
		if (aabb_overlap(baabb, cylinder_aabb(&s->cylinders[p])))
		{
			sb = (t_gjk_shape){&s->cylinders[p], gjk_support_cylinder, s->cylinders[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &bx->phys, &s->cylinders[p].phys, &bx->transform, &s->cylinders[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->rect_count && count < max)
		if (aabb_overlap(baabb, rect_aabb(&s->rects[p])))
		{
			sb = (t_gjk_shape){&s->rects[p], gjk_support_rect, s->rects[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &bx->phys, &s->rects[p].phys, &bx->transform, &s->rects[p].transform, &c[count]);
		}
	p = -1;
	while (++p < s->tri_count && count < max)
		if (aabb_overlap(baabb, tri_shape_aabb(&s->tris[p])))
		{
			sb = (t_gjk_shape){&s->tris[p], gjk_support_tri, s->tris[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &bx->phys, &s->tris[p].phys, &bx->transform, &s->tris[p].xform, &c[count]);
		}
	p = -1;
	while (++p < s->pyramid_count && count < max)
		if (aabb_overlap(baabb, pyramid_aabb(&s->pyramids[p])))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid, s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &bx->phys, &s->pyramids[p].phys, &bx->transform, &s->pyramids[p].transform, &c[count]);
		}
	return (count);
}
