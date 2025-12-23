/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:46:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

unsigned int	process_flat_color(t_scanline_draw_ctx *ctx)
{
	t_vec3	rgb;

	rgb.x = ctx->color_ctx.rgb1.x >> 16;
	rgb.y = ctx->color_ctx.rgb1.y >> 16;
	rgb.z = ctx->color_ctx.rgb1.z >> 16;
	return (rgb_to_int(create_color(rgb.x, rgb.y, rgb.z)));
}

unsigned int	process_shifted_color(t_scanline_draw_ctx *ctx, t_vec3 shift)
{
	t_vec3	rgb;

	rgb.x = ctx->color_ctx.rgb1.x >> 16;
	rgb.y = ctx->color_ctx.rgb1.y >> 16;
	rgb.z = ctx->color_ctx.rgb1.z >> 16;
	return (rgb_to_int(shift_color(create_color(rgb.x, rgb.y, rgb.z), shift)));
}
