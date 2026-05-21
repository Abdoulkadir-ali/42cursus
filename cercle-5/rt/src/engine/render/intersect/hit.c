/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	hit_object(const t_object *o, const t_ray *r, t_hit *h)
{
	if (o->type == OBJ_SPHERE)
		return (hit_sphere(&o->u.sph, r, h));
	if (o->type == OBJ_PLANE)
		return (hit_plane(&o->u.pln, r, h));
	if (o->type == OBJ_CYLINDER)
		return (hit_cylinder(&o->u.cyl, r, h));
	if (o->type == OBJ_BOX)
		return (hit_box(&o->u.box, r, h));
	if (o->type == OBJ_CAPSULE)
		return (hit_capsule(&o->u.cap, r, h));
	if (o->type == OBJ_PYRAMID)
		return (hit_pyramid(&o->u.pyr, r, h));
	if (o->type == OBJ_TRIANGLE)
		return (hit_triangle(&o->u.tri, r, h));
	return (0);
}

int	hit_planes(const t_object *planes, size_t n, const t_ray *r, t_hit *h)
{
	size_t	i;
	int		hit;

	hit = 0;
	i = 0;
	while (i < n)
	{
		if (hit_plane(&planes[i].u.pln, r, h))
		{
			h->obj_index = -(int)(i + 1);
			h->color = planes[i].color;
			hit = 1;
		}
		i++;
	}
	return (hit);
}

int	planes_occluded(const t_object *planes, size_t n, const t_ray *r, float max_t)
{
	size_t	i;
	t_hit	h;

	(void)max_t;
	i = 0;
	while (i < n)
	{
		h.t = T_MAX;
		if (hit_plane(&planes[i].u.pln, r, &h))
			return (1);
		i++;
	}
	return (0);
}
