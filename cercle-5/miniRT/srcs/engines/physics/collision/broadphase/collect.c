/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Collects all dynamic actor bodies from the scene.
 * Fixed: Now includes spheres, boxes, capsules, and cylinders.
 */
size_t	collect_bodies(t_scene *s, t_physics_body **out, size_t max)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (i < (size_t)s->sphere_count && n < max)
	{
		if (!s->spheres[i].phys.is_static)
			out[n++] = &s->spheres[i].phys;
		i++;
	}
	i = 0;
	while (i < (size_t)s->box_count && n < max)
	{
		if (!s->boxes[i].phys.is_static)
			out[n++] = &s->boxes[i].phys;
		i++;
	}
	i = 0;
	while (i < (size_t)s->capsule_count && n < max)
	{
		if (!s->capsules[i].phys.is_static)
			out[n++] = &s->capsules[i].phys;
		i++;
	}
	i = 0;
	while (i < (size_t)s->cylinder_count && n < max)
	{
		if (!s->cylinders[i].phys.is_static)
			out[n++] = &s->cylinders[i].phys;
		i++;
	}
	return (n);
}
