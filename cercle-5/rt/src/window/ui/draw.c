/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:41:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

static inline unsigned int	blend_pix(unsigned int dst, unsigned int src)
{
	unsigned int	a;
	unsigned int	ia;
	unsigned int	dr;
	unsigned int	dg;
	unsigned int	db;
	unsigned int	sr;
	unsigned int	sg;
	unsigned int	sb;

	a = (src >> 24) & 0xFF;
	if (a == 0)
		return (dst);
	if (a == 255)
		return (src & 0x00FFFFFF);
	ia = 255 - a;
	sr = (src >> 16) & 0xFF;
	sg = (src >> 8) & 0xFF;
	sb = src & 0xFF;
	dr = (dst >> 16) & 0xFF;
	dg = (dst >> 8) & 0xFF;
	db = dst & 0xFF;
	dr = (sr * a + dr * ia) >> 8;
	dg = (sg * a + dg * ia) >> 8;
	db = (sb * a + db * ia) >> 8;
	return ((dr << 16) | (dg << 8) | db);
}

void	gfx_pixel_blend(t_app *app, int x, int y, unsigned int rgba)
{
	unsigned int	*p;

	if (x < 0 || y < 0 || x >= app->img.w || y >= app->img.h)
		return ;
	if (app->ui.scissor_y1 > 0 && (y < app->ui.scissor_y0 || y >= app->ui.scissor_y1))
		return ;
	p = (unsigned int *)(app->img.addr + y * app->img.line_len + x * 4);
	*p = blend_pix(*p, rgba);
}

void	gfx_fill_rect(t_app *app, int x, int y, int w, int h, unsigned int rgba)
{
	int				ix, iy;
	unsigned int	*line;
	unsigned int	a = (rgba >> 24) & 0xFF;
	int				y0 = y;
	int				y1 = y + h;

	if (x < 0) { w += x; x = 0; }
	if (x + w > app->img.w) w = app->img.w - x;
	if (app->ui.scissor_y1 > 0)
	{
		if (y0 < app->ui.scissor_y0) y0 = app->ui.scissor_y0;
		if (y1 > app->ui.scissor_y1) y1 = app->ui.scissor_y1;
	}
	if (y0 < 0) y0 = 0;
	if (y1 > app->img.h) y1 = app->img.h;
	h = y1 - y0;
	if (w <= 0 || h <= 0 || a == 0) return ;

	if (a == 255)
	{
		unsigned int c = rgba & 0x00FFFFFF;
		for (iy = 0; iy < h; iy++)
		{
			line = (unsigned int *)(app->img.addr + (y0 + iy) * app->img.line_len);
			for (ix = 0; ix < w; ix++)
				line[x + ix] = c;
		}
	}
	else
	{
		for (iy = 0; iy < h; iy++)
		{
			line = (unsigned int *)(app->img.addr + (y0 + iy) * app->img.line_len);
			for (ix = 0; ix < w; ix++)
				line[x + ix] = blend_pix(line[x + ix], rgba);
		}
	}
}

void	gfx_rect_outline(t_app *app, int x, int y, int w, int h,
				unsigned int rgba)
{
	gfx_fill_rect(app, x, y, w, 1, rgba);
	gfx_fill_rect(app, x, y + h - 1, w, 1, rgba);
	gfx_fill_rect(app, x, y, 1, h, rgba);
	gfx_fill_rect(app, x + w - 1, y, 1, h, rgba);
}

static void	project_bounds(t_app *app, t_aabb b, int *x0, int *y0, int *x1, int *y1)
{
	t_vec3	pts[8];
	int		i;
	float	z, sx, sy;
	t_vec3	cp;

	pts[0] = b.min; pts[1] = v3(b.max.x, b.min.y, b.min.z);
	pts[2] = v3(b.min.x, b.max.y, b.min.z); pts[3] = v3(b.max.x, b.max.y, b.min.z);
	pts[4] = v3(b.min.x, b.min.y, b.max.z); pts[5] = v3(b.max.x, b.min.y, b.max.z);
	pts[6] = v3(b.min.x, b.max.y, b.max.z); pts[7] = b.max;
	*x0 = app->img.w; *y0 = app->img.h; *x1 = 0; *y1 = 0;
	for (i = 0; i < 8; i++)
	{
		cp = v3_sub(pts[i], app->scene.cam.pos);
		z = v3_dot(cp, app->scene.cam.dir);
		if (z < 0.1f) continue ;
		sx = (v3_dot(cp, app->scene.cam.right) / (z * app->scene.cam.half_w) + 1.0f) * 0.5f * app->img.w;
		sy = (1.0f - v3_dot(cp, app->scene.cam.up) / (z * app->scene.cam.half_h)) * 0.5f * app->img.h;
		if (sx < *x0) *x0 = (int)sx;
		if (sx > *x1) *x1 = (int)sx;
		if (sy < *y0) *y0 = (int)sy;
		if (sy > *y1) *y1 = (int)sy;
	}
	*x0 = ft_clampi(*x0 - 2, 1, app->img.w - 2);
	*y0 = ft_clampi(*y0 - 2, 1, app->img.h - 2);
	*x1 = ft_clampi(*x1 + 2, 1, app->img.w - 2);
	*y1 = ft_clampi(*y1 + 2, 1, app->img.h - 2);
}

void	gfx_outline_object(t_app *app, int target)
{
	int	x, y, idx, w, gid, x0, y0, x1, y1;
	t_aabb	b;
	t_aabb	ob;

	if (!app->pick.ids || target == 0x7fffffff) return ;
	gid = 0;
	if (target >= 0 && target < (int)(int)app->scene.n_bvh)
	{
		gid = app->scene.bvh_objs[target].group_id;
		if (gid > 0)
		{
			b = (t_aabb){v3(1e6, 1e6, 1e6), v3(-1e6, -1e6, -1e6)};
			for (int i = 0; i < (int)(int)app->scene.n_bvh; i++)
			{
				if (app->scene.bvh_objs[i].group_id == gid)
				{
					ob = object_bounds(&app->scene.bvh_objs[i]);
					aabb_union(&b, &ob);
				}
			}
		}
		else b = object_bounds(&app->scene.bvh_objs[target]);
	}
	else if (target < 0) b = object_bounds(&app->scene.planes[-target - 1]);
	else return ;
	project_bounds(app, b, &x0, &y0, &x1, &y1);
	if (x0 >= x1 || y0 >= y1) return ;
	w = app->pick.w;
	for (y = y0; y <= y1; y++)
	{
		for (x = x0; x <= x1; x++)
		{
			idx = app->pick.ids[y * w + x];
			if (idx == target || (gid > 0 && idx >= 0 && idx < (int)(int)app->scene.n_bvh && app->scene.bvh_objs[idx].group_id == gid))
			{
				int n[4] = {app->pick.ids[y*w+x-1], app->pick.ids[y*w+x+1], app->pick.ids[(y-1)*w+x], app->pick.ids[(y+1)*w+x]};
				for (int i = 0; i < 4; i++)
				{
					if (n[i] != target && !(gid > 0 && n[i] >= 0 && n[i] < (int)(int)app->scene.n_bvh && app->scene.bvh_objs[n[i]].group_id == gid))
					{
						gfx_pixel_blend(app, x, y, UI_COL_OUTLINE);
						break ;
					}
				}
			}
		}
	}
}