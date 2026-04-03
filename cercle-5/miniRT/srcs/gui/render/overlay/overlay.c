/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:46:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int c)
{
	char	buf[128];
	int		bh;
	int		ox;

	bh = gui->win.disp_size.y;
	ox = 220 + 16;
	snprintf(buf, sizeof(buf), "POS  %.2f  %.2f  %.2f", ctrl->transform.pos.x,
		ctrl->transform.pos.y, ctrl->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, ox, bh - 56, c, buf);
	snprintf(buf, sizeof(buf), "ROT  %.1f  %.1f", ctrl->transform.rotation.pitch
		* 57.29, ctrl->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, ox, bh - 36, c, buf);
}

static void	draw_ui_fps(t_gui *gui)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "%.0f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.disp_size.x - 108, 40,
		0x20E060, buf);
}

void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl)
{
	int	y;

	draw_scene_panel_bg(gui);
	draw_inspector_bg(gui);
	y = 38;
	draw_ui_help(gui, &y);
	draw_ui_status(gui, &y);
	draw_ui_object(gui);
	draw_ui_text_footer(gui, ctrl, 0xD0D0D8);
	draw_ui_fps(gui);
	draw_scene_panel_text(gui);
	draw_inspector_text(gui);
	widget_draw_all(gui);
}
