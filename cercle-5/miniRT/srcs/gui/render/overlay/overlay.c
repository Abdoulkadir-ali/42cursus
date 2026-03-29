/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 14:02:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int c)
{
	char	buf[128];
	int		bh;
	int		ox;

	bh = gui->win.disp_size.y;
	ox = SCENE_PANEL_W + 24;
	snprintf(buf, sizeof(buf), "Position  %.1f  %.1f  %.1f",
		ctrl->transform.pos.x, ctrl->transform.pos.y, ctrl->transform.pos.z);
	gui_draw_string(gui, buf, ox, bh - 52, c);
	snprintf(buf, sizeof(buf), "Rotation  %.1f  %.1f",
		ctrl->transform.rotation.pitch * 57.29,
		ctrl->transform.rotation.yaw * 57.29);
	gui_draw_string(gui, buf, ox, bh - 32, c);
}

static void	draw_ui_fps(t_gui *gui)
{
	char	buf[32];

	snprintf(buf, sizeof(buf), "%.0f FPS", gui->render.fps);
	gui_draw_string(gui, buf, gui->win.disp_size.x - 100, 32, COL_FPS);
}

void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl)
{
	int	y;

	y = 38;
	draw_ui_help(gui, &y);
	draw_ui_status(gui, &y);
	draw_ui_object(gui);
	draw_ui_text_footer(gui, ctrl, COL_TEXT_DIM);
	draw_ui_fps(gui);
	widget_draw_all(gui);
	draw_scene_panel_text(gui);
	draw_inspector_text(gui);
	draw_popup(gui);
}
