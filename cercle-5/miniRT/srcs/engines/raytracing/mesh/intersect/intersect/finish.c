/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_finish.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_finish_hit(t_trace_ctx *ctx, t_mesh *mesh, t_hit *hit,
		const t_ray *ray)
{
	t_mesh_hit_ctx	hit_ctx;

	if (ctx->best_tri == -1)
		return (false);
	hit_ctx.hit = hit;
	hit_ctx.mesh = mesh;
	hit_ctx.ray = ray;
	hit_ctx.bary = ctx->best_uv;
	hit_ctx.t = ctx->best_t;
	hit_ctx.tri = ctx->best_tri;
	update_mesh_hit(&hit_ctx);
	return (true);
}
