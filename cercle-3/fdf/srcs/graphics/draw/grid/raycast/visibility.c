/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:27:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Reject filled primitives that fall fully outside the visible strip.
 * @param ctx Surface-draw context containing strip bounds and margin.
 */
void	check_visibility(t_draw_surface_ctx *ctx)
{
	if ((ctx->g->render_config.filled
			|| ctx->g->render_config.render_mode == RENDER_TRIANGLES))
	{
		if ((int)ctx->curr.pos.x < (int)ctx->t->min_visible_x - ctx->margin
			|| (int)ctx->curr.pos.x > (int)ctx->t->max_visible_x + ctx->margin)
			return ;
	}
}
