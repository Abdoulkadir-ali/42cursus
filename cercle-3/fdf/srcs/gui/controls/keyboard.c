/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:45:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:34:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "gui.h"

void	draw_action_keys(t_data *data, int *y)
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
	put_key(data, GUI_PADDING + 10, *y, "XK_Escape");
	put_text(data, GUI_PADDING + 120, *y, "Exit");
	*y += GUI_LINE_HEIGHT + 5;
}

void	draw_optimization_keys(t_data *data, int *y)
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

void	draw_keyboard_controls(t_data *data, int *y)
{
	put_text(data, GUI_PADDING, *y, "Movement:");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Arrows");
	put_text(data, GUI_PADDING + 120, *y, "Move");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Scroll");
	put_text(data, GUI_PADDING + 120, *y, "Zoom");
	*y += GUI_LINE_HEIGHT;
	put_key(data, GUI_PADDING + 10, *y, "Ctrl + Arrows");
	put_text(data, GUI_PADDING + 120, *y, "Rotate");
	*y += GUI_LINE_HEIGHT + 5;
}
