/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:33:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_map_name_display_layout(t_layout *l, t_gui *gui)
{
	char	*map_name;

	gui_layout_title(l, "MAP");
	if (gui->maps->map_files && gui->maps->current_index >= 0
		&& (size_t)gui->maps->current_index < gui->maps->count)
	{
		map_name = gui->maps->map_files[gui->maps->current_index];
		gui_layout_label(l, map_name);
	}
	else
		gui_layout_label(l, "Test Grid");
}
