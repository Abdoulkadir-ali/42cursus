/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:28:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "gui.h"

void	draw_mouse_controls(t_data *data, int *y)
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
