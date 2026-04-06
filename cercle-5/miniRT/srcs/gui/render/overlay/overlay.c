/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:07:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int c)
{
	char		buf[128];
	const char	*name;
	t_vec2i		pos;

	if (!gui->scene)
		return ;
	name = "untitled";
	if (gui->scene->name)
		name = gui->scene->name;
	pos.y = gui->win.disp_size.y - 18;
	snprintf(buf, sizeof(buf), "%s  |  FOV %.0f°", name, ctrl->target_fov);
	pos.x = (gui->win.disp_size.x - ft_strlen(buf) * 6) / 2;
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x, pos.y, c, buf);
}

static void	draw_ui_fps(t_gui *gui)
{
	char	buf[128];
	t_vec2i	pos;

	pos.x = gui->win.disp_size.x - 108;
	snprintf(buf, sizeof(buf), "%.0f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x, 40, COL_FPS, buf);
	snprintf(buf, sizeof(buf), "%.0f RT", gui->render.render_fps);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x, 56, COL_UI_BLUE, buf);
}

/*
** Pixel-based UI: composited into the back buffer by the render thread
** before the triple-buffer flip.  back_idx is render-thread-private.
*/
void	draw_ui_pixels(t_gui *gui)
{
	draw_inspector_bg(gui);
	draw_scene_panel_bg(gui);
	draw_ui_orient(gui);
}

/*
** String-based UI: uses mlx_string_put which writes directly to X11.
** Called from gui_update on the main thread after the blit.
*/
void	draw_ui_strings(t_gui *gui, t_camera_controller *ctrl)
{
	int	y;

	y = 38;
	draw_ui_help(gui, &y);
	draw_ui_status(gui, &y);
	draw_ui_object(gui);
	draw_ui_text_footer(gui, ctrl, COL_TEXT);
	draw_ui_fps(gui);
	draw_scene_panel_text(gui);
	draw_inspector_text(gui);
	draw_settings(gui);
	draw_popup(gui);
	widget_draw_all(gui);
}
