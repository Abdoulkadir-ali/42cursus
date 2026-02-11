/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Blends two colors with alpha.
*/
static unsigned int	color_blend(unsigned int dst, int src, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = ((src >> 16) & 0xFF) * alpha + ((dst >> 16) & 0xFF) * (1.0 - alpha);
	g = ((src >> 8) & 0xFF) * alpha + ((dst >> 8) & 0xFF) * (1.0 - alpha);
	b = (src & 0xFF) * alpha + (dst & 0xFF) * (1.0 - alpha);
	return ((r << 16) | (g << 8) | b);
}

/*
** Draws a semi-transparent panel with a border.
*/
void	draw_panel(t_gui *gui, int x, int y, int w, int h, int bg, int brd)
{
	int		i;
	int		j;
	char	*dst;
	int		col;
	float	a;

	j = y;
	while (j < y + h)
	{
		i = x;
		while (i < x + w)
		{
			if (i >= 0 && i < gui->win.width && j >= 0 && j < gui->win.height)
			{
				dst = gui->win.addr + (j * gui->win.line_len + i * 4);
				col = (i == x || i == x + w - 1 || j == y || j == y + h - 1)
					? brd : bg;
				a = (col == brd) ? 0.9 : 0.65;
				*(unsigned int *)dst = color_blend(*(unsigned int *)dst, col, a);
			}
			i++;
		}
		j++;
	}
}

/*
** Draws UI overlays (info panels).
*/
/*
** Draws UI panels to the image buffer.
*/
void	draw_ui_panels(t_gui *gui)
{
	int		gold;

	gold = 0xD0A000;
	draw_panel(gui, 15, 15, 300, 110, 0x050505, gold);
	draw_panel(gui, 15, gui->win.height - 65, 450, 50, 0x050505, 0x444444);
	draw_panel(gui, gui->win.width - 110, 15, 95, 35, 0x050505, 0x00FF00);
}

/*
** Draws UI text to the window.
*/
void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl)
{
	char	buf[128];
	int		gold;
	int		wht;

	gold = 0xD0A000;
	wht = 0xEEEEEE;
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 35, gold, ">>> minRT SYSTEM v1.0");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 60, wht, "MOVE: WASD/SPACE/SHIFT");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 80, wht, "VIEW: LMB+DRAG");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 100, wht, "FOV : MMB+DRAG");
	snprintf(buf, sizeof(buf), "POS: %.2f %.2f %.2f", ctrl->transform.pos.x,
		ctrl->transform.pos.y, ctrl->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 30, gui->win.height - 52, wht, buf);
	snprintf(buf, sizeof(buf), "ROT: %.1f %.1f", ctrl->transform.rotation.pitch * 57.29,
		ctrl->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, 30, gui->win.height - 35, wht, buf);
	snprintf(buf, sizeof(buf), "%.1f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.width - 100, 37, 0x00FF00, buf);
}
