/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:16:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int c)
{
	char buf[128];
	int bh;

	bh = gui->win.disp_h;
	snprintf(buf, sizeof(buf), "POS  %.2f  %.2f  %.2f", ctrl->transform.pos.x,
		ctrl->transform.pos.y, ctrl->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 32, bh - 56, c, buf);
	snprintf(buf, sizeof(buf), "ROT  %.1f\xc2\xb0  %.1f\xc2\xb0",
		ctrl->transform.rotation.pitch * 57.29, ctrl->transform.rotation.yaw
		* 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, 32, bh - 36, c, buf);
}

static void	draw_ui_fps(t_gui *gui)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "%.0f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.disp_w - 108, 40,
		COL_FPS, buf);
}

void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl)
{
	int	y;

	y = 38;
	draw_ui_help(gui, &y);
	draw_ui_status(gui, &y);
	draw_ui_object(gui);
	draw_ui_text_footer(gui, ctrl, COL_TEXT);
	draw_ui_fps(gui);
	widget_draw_all(gui);
}
