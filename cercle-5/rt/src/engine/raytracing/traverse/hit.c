/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:19:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	hit_one(const t_object *o, const t_ray *r, t_hit *h)
{
	if (o->type == OBJ_SPHERE)
		return (hit_sphere(&o->u.sph, r, h));
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
