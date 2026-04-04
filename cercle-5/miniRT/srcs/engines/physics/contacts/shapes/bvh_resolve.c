/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_resolve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static bool	fill_ref_a(t_scene *s, t_bvh_ref ref, t_ref_data *d)
{
	if (ref.type == TYPE_BOX)
	{
		d->shape = (t_gjk_shape){&s->boxes[ref.index],
			gjk_support_box, s->boxes[ref.index].phys.pos};
		d->body = &s->boxes[ref.index].phys;
		d->xform = &s->boxes[ref.index].transform;
		return (true);
	}
	if (ref.type == TYPE_CAPSULE)
	{
		d->shape = (t_gjk_shape){&s->capsules[ref.index],
			gjk_support_capsule, s->capsules[ref.index].phys.pos};
		d->body = &s->capsules[ref.index].phys;
		d->xform = &s->capsules[ref.index].transform;
		return (true);
	}
	if (ref.type == TYPE_CYLINDER)
	{
		d->shape = (t_gjk_shape){&s->cylinders[ref.index],
			gjk_support_cylinder, s->cylinders[ref.index].phys.pos};
		d->body = &s->cylinders[ref.index].phys;
		d->xform = &s->cylinders[ref.index].transform;
		return (true);
	}
	return (false);
}

static bool	fill_ref_b(t_scene *s, t_bvh_ref ref, t_ref_data *d)
{
	if (ref.type == TYPE_RECT)
	{
		d->shape = (t_gjk_shape){&s->rects[ref.index],
			gjk_support_rect, s->rects[ref.index].phys.pos};
		d->body = &s->rects[ref.index].phys;
		d->xform = &s->rects[ref.index].transform;
		return (true);
	}
	if (ref.type == TYPE_TRI)
	{
		d->shape = (t_gjk_shape){&s->tris[ref.index],
			gjk_support_tri, s->tris[ref.index].phys.pos};
		d->body = &s->tris[ref.index].phys;
		d->xform = &s->tris[ref.index].xform;
		return (true);
	}
	if (ref.type == TYPE_PYRAMID)
	{
		d->shape = (t_gjk_shape){&s->pyramids[ref.index],
			gjk_support_pyramid, s->pyramids[ref.index].phys.pos};
		d->body = &s->pyramids[ref.index].phys;
		d->xform = &s->pyramids[ref.index].transform;
		return (true);
	}
	return (false);
}

bool	bvh_resolve_ref(t_scene *s, t_bvh_ref ref, t_ref_data *d)
{
	if (fill_ref_a(s, ref, d))
		return (true);
	return (fill_ref_b(s, ref, d));
}
