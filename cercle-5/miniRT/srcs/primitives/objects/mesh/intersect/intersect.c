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
	double	tmin;
	double	tmax;
	static int	_logged = 0;

	if (!_logged)
	{
		ft_print_debug("[MESH] intersect_mesh first call, tri_count=%zu bvh=%p\n",
			mesh ? mesh->tri_count : 0, (void *)(mesh ? mesh->bvh_nodes : NULL));
		fflush(stdout);
		_logged = 1;
	}
	if (!mesh || !mesh->bvh_nodes)
		return (false);
	if (!aabb_intersect_fast(&mesh->bvh_nodes[0].bbox, ray, &tmin, &tmax))
		return (false);
	PROF_INC(g_mesh_calls);
	intersect_init(&trace, hit);
	trace.node_count = 0;
	trace.tri_count = 0;
	intersect_traverse_mesh(mesh, ray, &trace);
	static int _slow_logged = 0;
	if (!_slow_logged && (trace.node_count > 500 || trace.tri_count > 500))
	{
		ft_print_debug("[MESH] SLOW RAY: nodes=%zu tris=%zu (tri_total=%zu)\n",
			trace.node_count, trace.tri_count, mesh->tri_count);
		fflush(stdout);
		_slow_logged = 1;
	}
	if (trace.best_tri.error)
		return (false);
	return (intersect_finish_hit(&trace, mesh, hit, ray));
}
