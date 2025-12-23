/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:37:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_performance_display_layout(t_layout *l, t_gui *gui)
{
	char	buffer[50];

	gui_layout_title(l, "OPTIMIZATIONS");
	display_point_stats(l, gui, buffer);
	format_float(gui->camera->z_scale, buffer);
	gui_layout_key_value(l, "Z-Scale (Z):", buffer);
	display_toggle_options(l, gui, buffer);
	display_algorithm_info(l, gui);
	display_tesselation_info(l, gui, buffer);
}
