/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 08:57:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "profiler.h"

static void	log_first_call(t_mesh *mesh)
{
	static int	logged = 0;
	size_t		tc;
	void		*bvh;

	if (logged)
		return ;
	tc = 0;
	bvh = NULL;
	if (mesh)
	{
		tc = mesh->tri_count;
		bvh = (void *)mesh->bvh_nodes;
	}
	ft_print_debug("[MESH] intersect_mesh first, tc=%zu bvh=%p\n", tc, bvh);
	fflush(stdout);
	logged = 1;
}

static void	log_slow_ray(t_trace *trace, t_mesh *mesh)
{
	static int	logged = 0;

	if (logged || (trace->node_count <= 500 && trace->tri_count <= 500))
		return ;
	ft_print_debug("[MESH] SLOW: nodes=%zu tris=%zu total=%zu\n",
		trace->node_count, trace->tri_count, mesh->tri_count);
	fflush(stdout);
	logged = 1;
}

bool	intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit)
{
	t_trace	trace;
	double	tmin;
	double	tmax;

	log_first_call(mesh);
	if (!mesh || !mesh->bvh_nodes)
		return (false);
	if (!aabb_intersect_fast(&mesh->bvh_nodes[0].bbox, ray, &tmin, &tmax))
		return (false);
	PROF_INC(mesh_calls);
	intersect_init(&trace, hit);
	trace.node_count = 0;
	trace.tri_count = 0;
	intersect_traverse_mesh(mesh, ray, &trace);
	log_slow_ray(&trace, mesh);
	if (trace.best_tri.error)
		return (false);
	return (intersect_finish_hit(&trace, mesh, hit, ray));
}
