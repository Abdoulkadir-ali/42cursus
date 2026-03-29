/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:02:28 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:59:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_sphere(t_physics *phys, int idx, t_contact *c, int count, int max)
{
	t_gjk_shape	sa;
	t_aabb		aabb;

	if (phys->scene->primitives.is_static[idx])
		return (count);
	aabb = get_primitive_aabb_soa(&phys->scene->primitives, idx);
	init_gjk_shape(&sa, phys, idx);
	count = prim_plane_contacts(phys, idx, c, count, max);
	return (prim_others_contacts(phys, idx, aabb, &sa, c, count, max));
}
