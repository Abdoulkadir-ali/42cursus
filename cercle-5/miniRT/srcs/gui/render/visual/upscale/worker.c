/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale_worker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/13 02:51:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"
#include <math.h>

/* No-depth path: weights always sum to 1 → skip w check and 1/w division. */
static void	blend_pixel_unit(struct s_upscale *ctx, int px, float wf[4])
{
	t_vec3f	b;

	if (px != ctx->last_px)
	{
		ctx->cache[0] = rt_unpack_color(ctx->row[0][px]);
		ctx->cache[1] = rt_unpack_color(ctx->row[0][px + 1]);
		ctx->cache[2] = rt_unpack_color(ctx->row[1][px]);
		ctx->cache[3] = rt_unpack_color(ctx->row[1][px + 1]);
		ctx->last_px = px;
	}
	b.x = ctx->cache[0].x * wf[0] + ctx->cache[1].x * wf[1]
		+ ctx->cache[2].x * wf[2] + ctx->cache[3].x * wf[3];
	b.y = ctx->cache[0].y * wf[0] + ctx->cache[1].y * wf[1]
		+ ctx->cache[2].y * wf[2] + ctx->cache[3].y * wf[3];
	b.z = ctx->cache[0].z * wf[0] + ctx->cache[1].z * wf[1]
		+ ctx->cache[2].z * wf[2] + ctx->cache[3].z * wf[3];
	b.w = 0.0f;
	ctx->out[0] = rt_pack_color(b);
}

/* Depth path: some weights may be zeroed -> must normalise. */
static void	blend_pixel(struct s_upscale *ctx, int px, float wf[4])
{
	t_vec3f		b;
	float		w;

	if (px != ctx->last_px)
	{
		ctx->cache[0] = rt_unpack_color(ctx->row[0][px]);
		ctx->cache[1] = rt_unpack_color(ctx->row[0][px + 1]);
		ctx->cache[2] = rt_unpack_color(ctx->row[1][px]);
		ctx->cache[3] = rt_unpack_color(ctx->row[1][px + 1]);
		ctx->last_px = px;
	}
	w = wf[0] + wf[1] + wf[2] + wf[3];
	if (w < 1e-6f)
		ctx->out[0] = rt_pack_color(ctx->cache[0]);
	else
	{
		b.x = (ctx->cache[0].x * wf[0] + ctx->cache[1].x * wf[1]
				+ ctx->cache[2].x * wf[2] + ctx->cache[3].x * wf[3]) / w;
		b.y = (ctx->cache[0].y * wf[0] + ctx->cache[1].y * wf[1]
				+ ctx->cache[2].y * wf[2] + ctx->cache[3].y * wf[3]) / w;
		b.z = (ctx->cache[0].z * wf[0] + ctx->cache[1].z * wf[1]
				+ ctx->cache[2].z * wf[2] + ctx->cache[3].z * wf[3]) / w;
		b.w = 0.0f;
		ctx->out[0] = rt_pack_color(b);
	}
}

static void	apply_depth_thresh(struct s_upscale *u, int src_x, float wf[4])
{
	const float	*d0 = u->depth[0] + src_x;
	const float	*d1 = u->depth[1] + src_x;
	const float	d00 = d0[0];

	if (d00 > 1e-4f)
	{
		if (fabsf(d0[1] - d00) / d00 > DEPTH_THRESH)
			wf[1] = 0.0f;
		if (fabsf(d1[0] - d00) / d00 > DEPTH_THRESH)
			wf[2] = 0.0f;
		if (fabsf(d1[1] - d00) / d00 > DEPTH_THRESH)
			wf[3] = 0.0f;
	}
}

static void	do_upscale_loop(t_gui *gui, struct s_upscale *u,
				float omy, float fy)
{
	int		x;
	int		src_x;
	float	wf[4];
	double	f;

	x = -1;
	while (++x < (int)gui->win.disp_size.x)
	{
		f = (double)x * (double)gui->win.size.x / (double)gui->win.disp_size.x;
		src_x = (int)f;
		f -= (double)src_x;
		wf[0] = (1.0f - (float)f) * omy;
		wf[1] = (float)f * omy;
		wf[2] = (1.0f - (float)f) * fy;
		wf[3] = (float)f * fy;
		if (u->depth[0])
			apply_depth_thresh(u, src_x, wf);
		if (!u->depth[0])
			blend_pixel_unit(u, src_x, wf);
		else
			blend_pixel(u, src_x, wf);
		u->out++;
	}
}

void	upscale_row(t_gui *gui, t_vec2i dst, double ry)
{
	struct s_upscale	u;
	const float			fy = (float)(ry - (int)ry);
	const float			omy = 1.0f - fy;
	const int			sw = (int)gui->win.size.x;

	ft_memset(&u, 0, sizeof(struct s_upscale));
	u.last_px = -1;
	u.row[0] = (uint32_t *)gui->win.addr + sw * (int)ry;
	u.row[1] = u.row[0] + sw;
	u.out = (uint32_t *)gui->win.disp_addrs[gui->render.back_idx]
		+ (size_t)dst.y * (gui->win.disp_line_len / 4);
	if (gui->opts.depth_buf)
	{
		u.depth[0] = gui->opts.depth_buf + sw * (int)ry;
		u.depth[1] = u.depth[0] + sw;
	}
	do_upscale_loop(gui, &u, omy, fy);
}
