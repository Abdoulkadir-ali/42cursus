/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:23:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui.h"

static void	put_text(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_TEXT_COLOR, text);
}

static void	put_key(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_KEY_COLOR, text);
}

static void	put_title(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_TITLE_COLOR, text);
}

static void	draw_mouse_controls(t_data *data, int *y)
{
	put_text(data, GUI_PADDING, *y, "Mouse:");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "LMB + Drag");
	put_text(data, GUI_PADDING + 120, *y, "Obj Rotate");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "RMB + Drag");
	put_text(data, GUI_PADDING + 120, *y, "Cam Rotate");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "MMB + Drag");
	put_text(data, GUI_PADDING + 120, *y, "Color Shift");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Shift + Drag");
	put_text(data, GUI_PADDING + 120, *y, "Depth Cut");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Scroll");
	put_text(data, GUI_PADDING + 120, *y, "Zoom");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Ctrl + Scroll");
	put_text(data, GUI_PADDING + 120, *y, "Zoom Speed");
	*y += GUI_LINE_HEIGHT + 5;
}

static void	draw_keyboard_controls(t_data *data, int *y)
{
	put_text(data, GUI_PADDING, *y, "Keyboard:");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Arrow Keys");
	put_text(data, GUI_PADDING + 120, *y, "Move");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Ctrl + Up");
	put_text(data, GUI_PADDING + 120, *y, "Speed ++");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Ctrl + Down");
	put_text(data, GUI_PADDING + 120, *y, "Speed --");
	*y += GUI_LINE_HEIGHT;
}

static void	draw_action_keys(t_data *data, int *y)
{
	put_key(data, GUI_PADDING + 10, *y, "P");
	put_text(data, GUI_PADDING + 120, *y, "Projection");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "N");
	put_text(data, GUI_PADDING + 120, *y, "Next Map");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "S");
	put_text(data, GUI_PADDING + 120, *y, "Style");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "A");
	put_text(data, GUI_PADDING + 120, *y, "Algorithm");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "X");
	put_text(data, GUI_PADDING + 120, *y, "Z-Divisor");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "I");
	put_text(data, GUI_PADDING + 120, *y, "Invert Move");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "V");
	put_text(data, GUI_PADDING + 120, *y, "Depth Cull");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "R");
	put_text(data, GUI_PADDING + 120, *y, "Reset View");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "ESC");
	put_text(data, GUI_PADDING + 120, *y, "Exit");
	*y += GUI_LINE_HEIGHT + 5;
}

static void	draw_optimization_keys(t_data *data, int *y)
{
	put_text(data, GUI_PADDING, *y, "Optimizations:");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "L + +/-");
	put_text(data, GUI_PADDING + 120, *y, "LOD Level");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Z + +/-");
	put_text(data, GUI_PADDING + 120, *y, "Z-Scale");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "F + +/-");
	put_text(data, GUI_PADDING + 120, *y, "Frustum");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "D + +/-");
	put_text(data, GUI_PADDING + 120, *y, "Depth Cut");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "T + +/-");
	put_text(data, GUI_PADDING + 120, *y, "Spline Seg");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "[Key] + 0");
	put_text(data, GUI_PADDING + 120, *y, "Reset");
}

void	draw_controls_guide_at(t_data *data, int *section_y)
{
	int	y;

	y = *section_y;
	put_title(data, GUI_PADDING, y, "CONTROLS");
	y += GUI_TITLE_HEIGHT;
	draw_mouse_controls(data, &y);
	draw_keyboard_controls(data, &y);
	draw_action_keys(data, &y);
	draw_optimization_keys(data, &y);
	*section_y = y;
}
