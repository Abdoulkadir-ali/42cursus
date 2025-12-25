/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:46:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:23:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_combo_value(t_layout *l, char *key, char *prefix, char *buffer);
void	format_uint(unsigned int num, char *buffer);

void	draw_rotation_section(t_layout *l)
{
	gui_layout_title(l, "ROTATION");
	gui_layout_key_value(l, "X/Y/Z", "Rotate Axis");
	gui_layout_key_value(l, "Q/E/U", "Align");
	gui_layout_key_value(l, "R", "Reset View");
	gui_layout_key_value(l, "W + +/-", "Rot Speed");
}

void	draw_mouse_controls(t_layout *l)
{
	gui_layout_label(l, "Mouse:");
	gui_layout_key_value(l, "LMB + Drag", "Obj Rotate");
	gui_layout_key_value(l, "RMB + Drag", "Cam Rotate");
	gui_layout_key_value(l, "MMB + Drag", "Color Shift");
	gui_layout_key_value(l, "Scroll", "Zoom");
}

void	draw_keyboard_controls(t_layout *l)
{
	gui_layout_label(l, "Keyboard:");
	gui_layout_key_value(l, "Arrows", "Move");
	gui_layout_key_value(l, "P", "Projection");
	gui_layout_key_value(l, "I", "Invert Move");
	gui_layout_key_value(l, "S", "Style");
	gui_layout_key_value(l, "PgUp/Dn", "Tes Level");
	gui_layout_key_value(l, "C", "Color Mode");
}

void	draw_combos_section(t_layout *l, t_gui *gui)
{
	char	buffer[50];

	gui_layout_title(l, "COMBOS");
	format_float(gui->camera->alpha, buffer);
	draw_combo_value(l, "A +/-", "Alpha: ", buffer);
	format_float(gui->camera->rotation_speed, buffer);
	draw_combo_value(l, "W +/-", "Rot Speed: ", buffer);
	if (gui->camera->use_z_divisor)
	{
		format_number((long long)gui->map->z_divisor, buffer);
		draw_combo_value(l, "T +/-", "Z-Divisor: ", buffer);
	}
	else
		draw_combo_value(l, "T +/-", "Z-Divisor: ", "OFF");
}

void	draw_optimizations_section(t_layout *l)
{
	gui_layout_title(l, "OPTIMIZATIONS");
	gui_layout_key_value(l, "+ / -", "Adjust Values");
}
