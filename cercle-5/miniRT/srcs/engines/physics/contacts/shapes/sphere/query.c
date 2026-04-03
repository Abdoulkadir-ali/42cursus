/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:45:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Main query function for sphere collision detection.
 */
size_t	query_sphere(t_contact_query *qu, size_t idx)
{
	size_t		j;
	t_sphere	*sp;
	t_gjk_shape	sa;

	sp = &qu->engine->scene->spheres[idx];
	if (sp->phys.is_static)
		return (qu->count);
	j = 0;
	while (j < qu->engine->scene->plane_count && qu->count < qu->max)
		sphere_vs_plane_analytic(sp, &qu->engine->scene->planes[j++], qu);
	if (qu->engine->scene->bvh)
		traverse_sphere_bvh(qu, idx, sp);
	sa = (t_gjk_shape){sp, gjk_support_sphere, sp->phys.pos};
	query_shapes(qu, &sa, &sp->phys, &sp->transform);
	return (qu->count);
}
