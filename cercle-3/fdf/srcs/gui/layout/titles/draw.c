/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:46:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 23:18:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_controls_guide_layout(t_layout *l, t_gui *gui)
{
	draw_rotation_section(l);
	gui_layout_add_spacer(l, 5);
	gui_layout_title(l, "CONTROLS");
	draw_mouse_controls(l);
	gui_layout_add_spacer(l, 5);
	draw_keyboard_controls(l);
	gui_layout_add_spacer(l, 5);
	draw_combos_section(l, gui);
	gui_layout_add_spacer(l, 5);
	draw_optimizations_section(l);
}
