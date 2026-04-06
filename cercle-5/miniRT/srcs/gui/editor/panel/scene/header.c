/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_scene_header_stats(t_gui *gui, t_vec2s d)
{
	char	buf[96];

	if (gui->rt_engine.stats.rays_frame > 0)
	{
		snprintf(buf, sizeof(buf), "%.1f ms  %zuK rays",
			gui->rt_engine.stats.last_render_ms,
			gui->rt_engine.stats.rays_frame / 1000);
		mlx_string_put(gui->win.mlx, gui->win.win,
			ui_sx(8, d), ui_sy(CRUD_PANEL_H - 14, d), COL_UI_DARK_GRAY, buf);
	}
}

static void	draw_scene_header_info(t_gui *gui, t_vec2s d)
{
	t_camera_controller	*c;
	char				buf[96];

	c = &gui->cam_ctrl;
	snprintf(buf, sizeof(buf), "POS  %.1f  %.1f  %.1f",
		c->transform.pos.x, c->transform.pos.y, c->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(36, d),
		COL_UI_LIGHT_BLUE, buf);
	snprintf(buf, sizeof(buf), "ROT  %.0f  %.0f",
		c->transform.rotation.pitch * 57.29, c->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(52, d),
		COL_UI_LIGHT_BLUE, buf);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(68, d),
		COL_UI_MUTED, "WASD Move  SPC/SHF Up/Dn");
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(82, d),
		COL_UI_MUTED, "LMB Look  X Phys  N/P Map");
}

void	draw_scene_header(t_gui *gui)
{
	t_vec2s	d;
	size_t	sw;

	d = gui->win.disp_size;
	sw = gui->scene_panel.width;
	draw_crud_btn(gui, (t_panel){vec2i(0, ui_sy(CRUD_PANEL_H - 1, d)),
		ui_size(sw, 1, d), COL_BORDER, COL_BORDER, ""});
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(16, d),
		COL_ACCENT, "miniRT");
	draw_scene_header_info(gui, d);
	draw_scene_header_stats(gui, d);
}
