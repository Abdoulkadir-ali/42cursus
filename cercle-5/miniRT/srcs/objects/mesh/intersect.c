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

#include "objects.h"

bool	intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit)
{
	t_trace_ctx	ctx;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	intersect_init_ctx(&ctx, hit);
	intersect_traverse_mesh(mesh, ray, &ctx);
	return (intersect_finish_hit(&ctx, mesh, hit, ray));
}
