/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "profiler.h"

void	process_mesh_leaf(t_mesh *mesh, t_mbvh_node *node, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_leaf_ctx	leaf;
	int			i;

	i = 0;
	while (i < node->count)
	{
		PROF_INC(g_mesh_tri_tests);
		leaf.tri = node->left_or_first + i;
		if (intersect_tri_precomp(ray, &mesh->tri_cache[leaf.tri],
				&leaf.t, &leaf.uv)
			&& leaf.t < ctx->best_t)
		{
			ctx->best_t = leaf.t;
			ctx->best_tri = leaf.tri;
			ctx->best_uv = leaf.uv;
		}
		i++;
	}
}
