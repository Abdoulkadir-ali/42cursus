/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 08:49:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, t_vec2i pos)
{
	int			col;
	uint32_t	*dst;

	col = panel_color(panel, pos);
	if (col == -1)
		return ;
	dst = (uint32_t *)(gui->win.disp_addrs[gui->render.back_idx]
			+ (pos.y * gui->win.disp_line_len
				+ pos.x * (gui->win.disp_bpp / 8)));
	*dst = color_blend(*dst, col, 0.85f);
}

static void	blend_row_span(uint32_t *row, int n, int col, float alpha)
{
	while (n-- > 0)
	{
		*row = color_blend(*row, col, alpha);
		row++;
	}
}

/*
** Corner rows (top/bottom r rows): rounded-corner check needed.
** Middle rows: left 2px border | bulk bg interior | right 2px border.
** No branches in the bulk path — fully vectorisable at -O3.
*/
static void	draw_panel_row(t_gui *gui, t_panel p, int y)
{
	const int	sz_x = (int)p.size.x;
	const int	stride = gui->win.disp_line_len / (gui->win.disp_bpp / 8);
	uint32_t	*row;
	t_vec2i		pos;

	if (y < PANEL_RADIUS || y >= (int)p.size.y - PANEL_RADIUS)
	{
		pos = vec2i(p.pos.x, p.pos.y + y);
		while (pos.x < p.pos.x + (int)p.size.x)
		{
			draw_panel_pixel(gui, p, pos);
			pos.x++;
		}
	}
	else
	{
		row = (uint32_t *)gui->win.disp_addrs[gui->render.back_idx]
			+ (p.pos.y + y) * stride + p.pos.x;
		blend_row_span(row, 2, p.brd, 0.85f);
		if (sz_x > 4)
			blend_row_span(row + 2, sz_x - 4, p.bg, 0.85f);
		blend_row_span(row + sz_x - 2, 2, p.brd, 0.85f);
	}
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	int	y;

	y = 0;
	while (y < (int)panel.size.y)
	{
		draw_panel_row(gui, panel, y);
		y++;
	}
}

void	draw_ui_panels(t_gui *gui)
{
	draw_scene_panel_bg(gui);
	draw_inspector_bg(gui);
}
