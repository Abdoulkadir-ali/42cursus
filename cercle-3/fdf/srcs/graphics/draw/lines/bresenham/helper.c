/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:25:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_bresenham_ctx(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->fp_r = (int)(p->r * (1 << FP_SHIFT));
	ctx->fp_g = (int)(p->green * (1 << FP_SHIFT));
	ctx->fp_b = (int)(p->b * (1 << FP_SHIFT));
	ctx->fp_dr = (int)(p->dr * (1 << FP_SHIFT));
	ctx->fp_dg = (int)(p->dg * (1 << FP_SHIFT));
	ctx->fp_db = (int)(p->db * (1 << FP_SHIFT));
	ctx->err = (int)p->delta.x - (int)p->delta.y;
	ctx->current = p->start;
}

int	bresenham_step_x(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->err -= p->delta.y;
	ctx->current.x += p->sign.x;
	if (ctx->current.x < 0 || ctx->current.x >= p->ctx.width)
		return (1);
	p->pixel_addr += p->ctx.step_x;
	if (p->z_addr)
		p->z_addr += p->ctx.z_step_x;
	return (0);
}

int	bresenham_step_y(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->err += p->delta.x;
	ctx->current.y += p->sign.y;
	if (ctx->current.y < 0 || ctx->current.y >= p->ctx.height)
		return (1);
	p->pixel_addr += p->ctx.step_y;
	if (p->z_addr)
		p->z_addr += p->ctx.z_step_y;
	return (0);
}

void	update_bresenham_colors(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	p->zr += p->z_step_val;
	ctx->fp_r += ctx->fp_dr;
	ctx->fp_g += ctx->fp_dg;
	ctx->fp_b += ctx->fp_db;
}

int	get_interpolated_color(t_bresenham_ctx *ctx)
{
	return (create_color(ctx->fp_r >> FP_SHIFT, ctx->fp_g >> FP_SHIFT,
			ctx->fp_b >> FP_SHIFT));
}
