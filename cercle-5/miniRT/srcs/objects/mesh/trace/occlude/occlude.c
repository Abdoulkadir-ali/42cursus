/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occlude.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "profiler.h"

bool	mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist)
{
	double	tmin;
	double	tmax;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	if (!aabb_intersect_fast(&mesh->bvh_nodes[0].bbox, ray, &tmin, &tmax)
		|| tmin >= dist)
		return (false);
	PROF_INC(g_mesh_occ_calls);
	return (traverse_occlude(mesh, ray, dist));
}
