/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 19:46:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_performance_display_layout(t_layout *l, t_gui *gui)
{
	char	buffer[50];

	gui_layout_title(l, "OPTIMIZATIONS");
	display_point_stats(l, gui, buffer);
	display_toggle_options(l, gui, buffer);
	display_algorithm_info(l, gui);
	display_tesselation_info(l, gui, buffer);
}
