/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

/**
 * @brief Primary entry point for sphere collision generation. 
 * Dispatches to BVH Broadphase, GJK Narrowphase, and Analytic Plane tests.
 */
int	query_sphere(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_sphere	*sp;
	t_aabb		sa;
	t_gjk_shape	sa_gjk;

	sp = &s->spheres[idx];
	if (sp->phys.is_static)
		return (count);
	sa = sphere_aabb(sp);
	sa_gjk = (t_gjk_shape){sp, gjk_support_sphere, sp->phys.center};
	count = traverse_bvh_contacts(s, idx, sp, sa, c, count, max);
	count = sphere_plane_contacts(s, sp, &sa_gjk, c, count, max);
	count = sphere_others_contacts(s, idx, sp, sa, &sa_gjk, c, count, max);
	return (count);
}
