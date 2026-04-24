/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 19:44:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_H
# define GUI_FUNCTIONS_H

# include "window.h"
# include "types.h"
# include "maths.h"
# include "libs.h"

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

static inline int	ui_sx(size_t x, t_vec2s disp)
{
	return ((int)(x * disp.x / UI_BASE_W));
}

static inline int	ui_sy(size_t y, t_vec2s disp)
{
	return ((int)(y * disp.y / UI_BASE_H));
}

static inline t_vec2i	ui_pos(size_t x, size_t y, t_vec2s disp)
{
	return (vec2i(x * disp.x / UI_BASE_W,
			y * disp.y / UI_BASE_H));
}

static inline t_vec2s	ui_size(size_t w, size_t h, t_vec2s disp)
{
	return (vec2s(w * disp.x / UI_BASE_W,
			h * disp.y / UI_BASE_H));
}

static inline bool	phit(t_vec2i m, t_vec2i pos, t_vec2s size)
{
	return (m.x >= pos.x && m.x < pos.x + (int)size.x
		&& m.y >= pos.y && m.y < pos.y + (int)size.y);
}

#endif
