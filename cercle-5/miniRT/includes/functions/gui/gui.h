/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:00:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_H
# define GUI_FUNCTIONS_H

# include "window.h"
# include "types.h"
# include "maths.h"

# define AXIS_COL_X 0xFF4040
# define AXIS_COL_Y 0x40FF40
# define AXIS_COL_Z 0x4080FF

/*
** UI coordinate helpers — define positions in 1920×1080 space, scale
** automatically to the actual display resolution at runtime.
**
**   ui_sx(x, disp)        — scale a single X value
**   ui_sy(y, disp)        — scale a single Y value
**   ui_pos(x, y, disp)    — scale a position → t_vec2i
**   ui_size(w, h, disp)   — scale a size     → t_vec2i
**
** Example:
**   mlx_string_put(..., ui_sx(960, gui->win.disp_size), ...);
**   draw_panel(gui, (t_panel){ui_pos(0, 0, d), ui_size(220, 1080, d), ...});
*/
# define UI_BASE_W 1920
# define UI_BASE_H 1080

static inline int	ui_sx(int x, t_vec2i disp)
{
	return (x * (int)disp.x / UI_BASE_W);
}

static inline int	ui_sy(int y, t_vec2i disp)
{
	return (y * (int)disp.y / UI_BASE_H);
}

static inline t_vec2i	ui_pos(int x, int y, t_vec2i disp)
{
	return (vec2i(x * (int)disp.x / UI_BASE_W,
			y * (int)disp.y / UI_BASE_H));
}

static inline t_vec2i	ui_size(int w, int h, t_vec2i disp)
{
	return (vec2i(w * (int)disp.x / UI_BASE_W,
			h * (int)disp.y / UI_BASE_H));
}

#endif
