/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remainder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:34:03 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:04:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	handle_remainder(t_handle_remainder_ctx *ctx)
{
	size_t	idx;
	t_point	p;

	while (ctx->i < ctx->width)
	{
		idx = ctx->row_idx + ctx->i;
		ctx->i++;
		if (ctx->g->map->points.pos[idx].z > BAD_VALUE + 1.0)
		{
			p.pos = ctx->g->map->points.pos[idx];
			p.color = ctx->g->map->points.color[idx];
			ctx->out[idx] = apply_transform(p, ctx->g->camera);
		}
		else
			ctx->out[idx].pos = create_vec3d(BAD_VALUE, BAD_VALUE, BAD_VALUE);
	}
}
