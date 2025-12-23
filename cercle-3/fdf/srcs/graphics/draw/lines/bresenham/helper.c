/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/23 22:31:02 by abdoali          ###   ########.fr       */
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

void	update_bresenham_colors(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	p->zr += p->z_step_val;
	ctx->fp_r += ctx->fp_dr;
	ctx->fp_g += ctx->fp_dg;
	ctx->fp_b += ctx->fp_db;
}

static int	bresenham_step_x(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->err -= p->delta.y;
	ctx->current.x += p->sign.x;
	p->pixel_addr += p->ctx.step_x;
	if (p->z_addr)
		p->z_addr += p->ctx.z_step_x;
	return (ctx->current.x < 0 || ctx->current.x >= (int)p->ctx.width);
}

static int	bresenham_step_y(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->err += p->delta.x;
	ctx->current.y += p->sign.y;
	p->pixel_addr += p->ctx.step_y;
	if (p->z_addr)
		p->z_addr += p->ctx.z_step_y;
	return (ctx->current.y < 0 || ctx->current.y >= (int)p->ctx.height);
}

int	bresenham_iter(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->e2 = 2 * ctx->err;
	if (ctx->e2 > -p->delta.y)
		if (bresenham_step_x(ctx, p))
			return (1);
	if (ctx->e2 < p->delta.x)
		if (bresenham_step_y(ctx, p))
			return (1);
	return (0);
}
