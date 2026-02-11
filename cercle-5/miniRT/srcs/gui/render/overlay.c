/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
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
void	draw_panel(t_gui *gui, t_panel panel)
{
	int		i;
	int		j;
	char	*dst;
	int		col;
	float	a;

	j = panel.y;
	while (j < panel.y + panel.h)
	{
		i = panel.x;
		while (i < panel.x + panel.w)
		{
			if (i >= 0 && i < gui->win.width && j >= 0 && j < gui->win.height)
			{
				dst = gui->win.addr + (j * gui->win.line_len + i * 4);
				col = panel.bg;
				if (i == panel.x || i == panel.x + panel.w - 1
					|| j == panel.y || j == panel.y + panel.h - 1)
					col = panel.brd;
				a = 0.65;
				if (col == panel.brd)
					a = 0.9;
				*(unsigned int *)dst = color_blend(*(unsigned int *)dst,
						col, a);
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
	t_panel	panel;

	gold = 0xD0A000;
	panel = (t_panel){15, 15, 300, 110, 0x050505, gold};
	draw_panel(gui, panel);
	panel = (t_panel){15, gui->win.height - 65, 450, 50,
		0x050505, 0x444444};
	draw_panel(gui, panel);
	panel = (t_panel){gui->win.width - 110, 15, 95, 35,
		0x050505, 0x00FF00};
	draw_panel(gui, panel);
}

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int wht)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "POS: %.2f %.2f %.2f", ctrl->transform.pos.x,
		ctrl->transform.pos.y, ctrl->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 30,
		gui->win.height - 52, wht, buf);
	snprintf(buf, sizeof(buf), "ROT: %.1f %.1f",
		ctrl->transform.rotation.pitch * 57.29,
		ctrl->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, 30,
		gui->win.height - 35, wht, buf);
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
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 35, gold,
		">>> minRT SYSTEM v1.0");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 60, wht,
		"MOVE: WASD/SPACE/SHIFT");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 80, wht, "VIEW: LMB+DRAG");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 100, wht, "FOV : MMB+DRAG");
	draw_ui_text_footer(gui, ctrl, wht);
	snprintf(buf, sizeof(buf), "%.1f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win,
		gui->win.width - 100, 37, 0x00FF00, buf);
}
