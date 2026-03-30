/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_trace_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "profiler.h"

bool	intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit)
{
	t_trace	trace;
	double		tmin;
	double		tmax;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	if (!aabb_intersect_fast(&mesh->bvh_nodes[0].bbox, ray, &tmin, &tmax))
		return (false);
	PROF_INC(g_mesh_calls);
	intersect_init(&trace, hit);
	intersect_traverse_mesh(mesh, ray, &trace);
	return (intersect_finish_hit(&trace, mesh, hit, ray));
}
