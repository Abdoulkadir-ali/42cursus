/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_trace_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@local>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 18:20:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit)
{
    t_trace_ctx	ctx;
    double		tmin;
    double		tmax;

    if (!mesh || !mesh->bvh_nodes)
        return (false);
    if (!aabb_intersect_fast(&mesh->bvh_nodes[0].bbox, ray, &tmin, &tmax))
        return (false);
    PROF_INC(g_mesh_calls);
    intersect_init_ctx(&ctx, hit);
    intersect_traverse_mesh(mesh, ray, &ctx);
    return (intersect_finish_hit(&ctx, mesh, hit, ray));
}
