/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, int i, int j)
{
	char	*dst;
	int		col;
	float	a;

	if (i < 0 || i >= gui->win.disp_w || j < 0 || j >= gui->win.disp_h)
		return ;
	col = panel_color(panel, i, j);
	if (col == -1)
		return ;
	dst = gui->win.disp_addr + (j * gui->win.disp_line_len + i * 4);
	a = 0.75;
	if (col == panel.brd)
		a = 0.90;
	*(unsigned int *)dst = color_blend(*(unsigned int *)dst, col, a);
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	int	i;
	int	j;

	j = panel.y;
	while (j < panel.y + panel.h)
	{
		i = panel.x;
		while (i < panel.x + panel.w)
		{
			draw_panel_pixel(gui, panel, i, j);
			i++;
		}
		j++;
	}
}

void	draw_ui_panels(t_gui *gui)
{
	t_panel	panel;
	int		bh;

	bh = gui->win.disp_h;
	panel = (t_panel){16, 16, 310, 120, COL_BG, COL_ACCENT};
	draw_panel(gui, panel);
	panel = (t_panel){16, bh - 72, 460, 56, COL_BG, COL_BORDER};
	draw_panel(gui, panel);
	panel = (t_panel){gui->win.disp_w - 120, 16, 104, 40, COL_BG, COL_FPS};
	draw_panel(gui, panel);
}

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int c)
{
	char	buf[128];
	int		bh;

	bh = gui->win.disp_h;
	snprintf(buf, sizeof(buf), "POS  %.2f  %.2f  %.2f",
		ctrl->transform.pos.x, ctrl->transform.pos.y,
		ctrl->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 32, bh - 56, c, buf);
	snprintf(buf, sizeof(buf), "ROT  %.1f\xc2\xb0  %.1f\xc2\xb0",
		ctrl->transform.rotation.pitch * 57.29,
		ctrl->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, 32, bh - 36, c, buf);
}

void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl)
{
	char	buf[128];

	mlx_string_put(gui->win.mlx, gui->win.win, 32, 38, COL_ACCENT,
		"miniRT");
	mlx_string_put(gui->win.mlx, gui->win.win, 32, 62, COL_TEXT,
		"WASD  Move   SPACE/SHIFT  Up/Down");
	mlx_string_put(gui->win.mlx, gui->win.win, 32, 82, COL_TEXT,
		"LMB   Look   MMB          Zoom");
	mlx_string_put(gui->win.mlx, gui->win.win, 32, 102, COL_TEXT,
		"+/-   Speed  N            Next map");
	draw_ui_text_footer(gui, ctrl, COL_TEXT);
	snprintf(buf, sizeof(buf), "%.0f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.disp_w - 108, 40,
		COL_FPS, buf);
}
