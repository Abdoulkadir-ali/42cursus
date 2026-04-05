/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:51:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_ui_text_footer(t_gui *gui, t_camera_controller *ctrl, int c)
{
	char	buf[128];
	int		bx;
	int		by;

	if (!gui->scene)
		return ;
	by = (int)gui->win.disp_size.y - 18;
	snprintf(buf, sizeof(buf), "%s  |  FOV %.0f°",
		gui->scene->name ? gui->scene->name : "untitled",
		ctrl->target_fov);
	bx = ((int)gui->win.disp_size.x - (int)ft_strlen(buf) * 6) / 2;
	mlx_string_put(gui->win.mlx, gui->win.win, bx, by, c, buf);
}

static void	draw_ui_fps(t_gui *gui)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "%.0f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.disp_size.x - 108, 40,
		0x20E060, buf);
	snprintf(buf, sizeof(buf), "%.0f RT", gui->render.render_fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.disp_size.x - 108, 56,
		0x60A0E0, buf);
}

static void	orient_put_pixel(t_gui *gui, t_vec2i p, int col)
{
	size_t	w;
	size_t	h;
	size_t	*dst;

	w = gui->win.disp_size.x;
	h = gui->win.disp_size.y;
	if (p.x >= w || p.y >= h)
		return ;
	dst = (size_t *)(gui->win.disp_addrs[gui->render.ui_buf_idx]
			+ (p.y * gui->win.disp_line_len
				+ p.x * (gui->win.disp_bpp / 8)));
	*dst = color_blend(*dst, col, 0.9f);
}

static void	orient_line(t_gui *gui, t_vec2i a, t_vec2i b, int col)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs((int)b.x - (int)a.x);
	dy = -abs((int)b.y - (int)a.y);
	sx = (a.x < b.x) ? 1 : -1;
	sy = (a.y < b.y) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		orient_put_pixel(gui, a, col);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			a.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			a.y += sy;
		}
	}
}

static void	orient_axis(t_gui *gui, t_vec2i c, t_vec3 v, int col)
{
	t_vec2i	e;
	t_vec2i	tip;
	int		len;
	int		tiplen;

	len = (int)(gui->win.disp_size.y / 24);
	tiplen = (int)(gui->win.disp_size.y / 192);
	e = vec2i(c.x + (int)(v.x * len), c.y - (int)(v.y * len));
	tip = vec2i(e.x - (int)(v.x * tiplen) - (int)(v.y * tiplen),
			e.y + (int)(v.y * tiplen) - (int)(v.x * tiplen));
	orient_line(gui, c, e, col);
	orient_line(gui, e, tip, col);
}

static void	draw_ui_orient(t_gui *gui)
{
	t_vec2i	c;
	int		off;

	off = (int)(gui->win.disp_size.y / 14);
	c = vec2i(gui->win.disp_size.x - off, gui->win.disp_size.y - off);
	orient_axis(gui, c, gui->cam_ctrl.transform.right, AXIS_COL_X);
	orient_axis(gui, c, gui->cam_ctrl.transform.up, AXIS_COL_Y);
	orient_axis(gui, c, gui->cam_ctrl.transform.forward, AXIS_COL_Z);
}

void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl)
{
	int	y;

	draw_inspector_bg(gui);
	y = 38;
	draw_ui_help(gui, &y);
	draw_ui_status(gui, &y);
	draw_ui_object(gui);
	draw_ui_text_footer(gui, ctrl, 0xD0D0D8);
	draw_ui_fps(gui);
	draw_ui_orient(gui);
	draw_scene_panel_bg(gui);
	draw_scene_panel_text(gui);
	draw_inspector_text(gui);
	draw_settings(gui);
	widget_draw_all(gui);
}
