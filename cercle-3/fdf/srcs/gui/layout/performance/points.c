/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:41:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:41:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_point_stats(t_layout *l, t_gui *gui, char *buffer)
{
	t_point_stats_ctx	ctx;

	ctx.total = (size_t)gui->map->width * (size_t)gui->map->height;
	ctx.level = gui->render_config->detail_level;
	if (ctx.level > 0)
	{
		ctx.multiplier = pow(4.0, (double)ctx.level);
		ctx.active = (size_t)(ctx.total * ctx.multiplier);
	}
	else
	{
		ctx.lod = gui->render_config->lod_value;
		if (ctx.lod < 1.0f)
			ctx.lod = 1.0f;
		ctx.active = (size_t)(ctx.total / (ctx.lod * ctx.lod));
	}
	format_number((long long)ctx.total, buffer);
	gui_layout_key_value(l, "Raw map points:", buffer);
	format_number((long long)ctx.active, buffer);
	gui_layout_key_value(l, "Active points:", buffer);
}
