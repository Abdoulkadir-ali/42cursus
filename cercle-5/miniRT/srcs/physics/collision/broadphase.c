/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadphase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/*
** Collect all dynamic compound bodies from the scene into a flat array.
** Returns the count of dynamic compound bodies found.
*/
static size_t	collect_bodies(t_scene *s, t_physics_body **out, size_t max)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (i < (size_t)s->sphere_count && n < max)
	{
		if (s->spheres[i].phys.is_compound && !s->spheres[i].phys.is_static)
			out[n++] = &s->spheres[i].phys;
		i++;
	}
	i = 0;
	while (i < (size_t)s->box_count && n < max)
	{
		if (s->boxes[i].phys.is_compound && !s->boxes[i].phys.is_static)
			out[n++] = &s->boxes[i].phys;
		i++;
	}
	return (n);
}

/*
** Test two global AABBs. Returns true if they overlap on all 3 axes.
*/
static bool	aabb_overlap_broad(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}

/**
 * @brief Global AABB broadphase for compound bodies.
 * Tests every pair of dynamic compound bodies. Returns candidate pair count.
 */
int	broadphase(t_scene *s, t_body_pair *out, int max)
{
	t_physics_body	*bodies[MAX_BODY_PAIRS];
	size_t			n;
	size_t			i;
	size_t			j;
	int				count;

	n = collect_bodies(s, bodies, MAX_BODY_PAIRS);
	count = 0;
	i = 0;
	while (i < n && count < max)
	{
		j = i + 1;
		while (j < n && count < max)
		{
			if (aabb_overlap_broad(bodies[i]->global_aabb, bodies[j]->global_aabb))
			{
				out[count].a = bodies[i];
				out[count].b = bodies[j];
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}
