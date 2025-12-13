/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:46:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:44:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_controls_guide_layout(t_layout *l, t_gui *gui)
{
	(void)gui;
	gui_layout_title(l, "CONTROLS");
	gui_layout_label(l, "Mouse:");
	gui_layout_key_value(l, "LMB + Drag", "Obj Rotate");
	gui_layout_key_value(l, "RMB + Drag", "Cam Rotate");
	gui_layout_key_value(l, "MMB + Drag", "Color Shift");
	gui_layout_key_value(l, "Scroll", "Zoom");
	gui_layout_add_spacer(l, 5);
	gui_layout_label(l, "Keyboard:");
	gui_layout_key_value(l, "Arrows", "Move");
	gui_layout_key_value(l, "P", "Projection");
	gui_layout_key_value(l, "I", "Invert Move");
	gui_layout_key_value(l, "V", "Depth Cull");
	gui_layout_add_spacer(l, 5);
	gui_layout_label(l, "Optimizations:");
	gui_layout_key_value(l, "+ / -", "Adjust Values");
}
