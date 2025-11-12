/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:46:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 20:21:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


void	draw_controls_guide_at(t_gui *gui, int *section_y)
{
	int	y;

	y = *section_y;
	put_colored(gui, GUI_PADDING, y, "CONTROLS", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	draw_mouse_controls(gui, &y);
	draw_keyboard_controls(gui, &y);
	draw_action_keys(gui, &y);
	draw_optimization_keys(gui, &y);
	*section_y = y;
}

void	draw_mouse_controls(t_gui *gui, int *y)
{
	const char *keys[] = {"LMB + Drag", "RMB + Drag", "MMB + Drag", "Shift + Drag", "Scroll", "Ctrl + Scroll"};
	const char *texts[] = {"Obj Rotate", "Cam Rotate", "Color Shift", "Depth Cut", "Zoom", "Zoom Speed"};
	int i = 0;

	put_text(gui, GUI_PADDING, *y, "Mouse:");
	*y += GUI_LINE_HEIGHT;
	while (i < 6)
	{
		put_key(gui, GUI_PADDING + 10, *y, (char *)keys[i]);
		put_text(gui, GUI_PADDING + 120, *y, (char *)texts[i]);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
	*y += 5;
}

void	draw_keyboard_controls(t_gui *gui, int *y)
{
	const char *keys[] = {"Arrows", "Scroll", "Ctrl + Arrows"};
	const char *texts[] = {"Move", "Zoom", "Rotate"};
	int i = 0;

	put_text(gui, GUI_PADDING, *y, "Movement:");
	*y += GUI_LINE_HEIGHT;
	while (i < 3)
	{
		put_key(gui, GUI_PADDING + 10, *y, (char *)keys[i]);
		put_text(gui, GUI_PADDING + 120, *y, (char *)texts[i]);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
	*y += 5;
}

void	draw_action_keys(t_gui *gui, int *y)
{
	const char *keys[] = {"P", "N", "S", "A", "X", "I", "V", "R", "XK_Escape"};
	const char *texts[] = {"Projection", "Next Map", "Style", "Algorithm", "Z-Divisor", "Invert Move", "Depth Cull", "Reset View", "Exit"};
	int i = 0;

	while (i < 9)
	{
		put_key(gui, GUI_PADDING + 10, *y, (char *)keys[i]);
		put_text(gui, GUI_PADDING + 120, *y, (char *)texts[i]);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
	*y += 5;
}

void	draw_optimization_keys(t_gui *gui, int *y)
{
	const char *keys[] = {"L + +/-", "Z + +/-", "F + +/-", "D + +/-", "T + +/-", "[Key] + 0"};
	const char *texts[] = {"LOD Level", "Z-Scale", "Frustum", "Depth Cut", "Spline Seg", "Reset"};
	int i = 0;

	put_text(gui, GUI_PADDING, *y, "Optimizations:");
	*y += GUI_LINE_HEIGHT;
	while (i < 6)
	{
		put_key(gui, GUI_PADDING + 10, *y, (char *)keys[i]);
		put_text(gui, GUI_PADDING + 120, *y, (char *)texts[i]);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
}
