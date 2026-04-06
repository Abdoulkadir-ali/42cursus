/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:24:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

/**
 * @brief Main query function for sphere collision detection.
 */
size_t	query_sphere(t_contact_query *qu, size_t idx)
{
	size_t			j;
	t_sphere		*sp;
	t_gjk_shape		sa;
	t_bvh_phys_ctx	ctx;

	sp = &qu->engine->scene->spheres[idx];
	if (sp->phys.is_static)
		return (qu->count);
	j = 0;
	while (j < qu->engine->scene->plane_count && qu->count < qu->max)
		sphere_vs_plane_analytic(sp, &qu->engine->scene->planes[j++], qu);
	traverse_sphere_bvh(qu, idx, sp);
	sa = init_gjk_shape(sp, gjk_support_sphere, sp->phys.pos);
	ctx = (t_bvh_phys_ctx){qu, &sa, &sp->phys, &sp->transform, TYPE_SPHERE};
	bvh_query_shapes(&ctx, sphere_aabb(sp));
	return (qu->count);
}
