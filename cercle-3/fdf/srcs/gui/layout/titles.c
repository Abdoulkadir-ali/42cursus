/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   titles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:46:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:36:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	draw_rotation_section(t_layout *l)
{
	gui_layout_title(l, "ROTATION");
	gui_layout_key_value(l, "X/Y/Z", "Rotate Axis");
	gui_layout_key_value(l, "Q/E/U", "Align");
	gui_layout_key_value(l, "R", "Reset View");
	gui_layout_key_value(l, "W + +/-", "Rot Speed");
}

static void	draw_mouse_controls(t_layout *l)
{
	gui_layout_label(l, "Mouse:");
	gui_layout_key_value(l, "LMB + Drag", "Obj Rotate");
	gui_layout_key_value(l, "RMB + Drag", "Cam Rotate");
	gui_layout_key_value(l, "MMB + Drag", "Color Shift");
	gui_layout_key_value(l, "Scroll", "Zoom");
}

static void	draw_keyboard_controls(t_layout *l)
{
	gui_layout_label(l, "Keyboard:");
	gui_layout_key_value(l, "Arrows", "Move");
	gui_layout_key_value(l, "P", "Projection");
	gui_layout_key_value(l, "I", "Invert Move");
	gui_layout_key_value(l, "V", "Depth Cull");
	gui_layout_key_value(l, "T", "Tessellation");
	gui_layout_key_value(l, "PgUp/Dn", "Tes Level");
	gui_layout_key_value(l, "G", "Gen Map (Noise)");
	gui_layout_key_value(l, "C", "Color Mode");
}

static void	draw_optimizations_section(t_layout *l)
{
	gui_layout_title(l, "OPTIMIZATIONS");
	gui_layout_key_value(l, "+ / -", "Adjust Values");
}

void	draw_controls_guide_layout(t_layout *l)
{
	draw_rotation_section(l);
	gui_layout_add_spacer(l, 5);
	gui_layout_title(l, "CONTROLS");
	draw_mouse_controls(l);
	gui_layout_add_spacer(l, 5);
	draw_keyboard_controls(l);
	gui_layout_add_spacer(l, 5);
	draw_optimizations_section(l);
}
