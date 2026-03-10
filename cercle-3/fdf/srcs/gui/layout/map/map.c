/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:48:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Check whether the current map pointer belongs to the loaded map list.
 * @param maps Map manager to inspect.
 * @return `1` if the current map is loaded from the list, otherwise `0`.
 */
static int	is_current_map_loaded(t_maps *maps)
{
	size_t	i;

	i = 0;
	while (i < maps->count)
	{
		if (maps->maps[i++] == maps->current_map)
			return (1);
	}
	return (0);
}

/**
 * @brief Draw the map section describing the active map source.
 * @param l Layout object controlling panel placement.
 * @param gui GUI object providing map-manager state.
 */
void	draw_map_layout(t_layout *l, t_gui *gui)
{
	char	*map_name;
	char	*id_str;
	char	*generated_name_full;

	gui_layout_title(l, "MAP");
	gui_layout_add_spacer(l, 5);
	gui_layout_key_value(l, "G", "Generate Noise Map");
	gui_layout_add_spacer(l, 40);
	if (gui->maps->current_map && !is_current_map_loaded(gui->maps))
	{
		id_str = ft_itoa(gui->maps->generated_id);
		generated_name_full = ft_strjoin("generated_", id_str);
		put_text(l->gui, l->x_start + 80, l->cursor_y, generated_name_full);
		free(id_str);
		free(generated_name_full);
	}
	else if (gui->maps->map_files && gui->maps->current_index >= 0
		&& (size_t)gui->maps->current_index < gui->maps->count)
	{
		map_name = gui->maps->map_files[gui->maps->current_index];
		put_text(l->gui, l->x_start + 80, l->cursor_y, map_name);
	}
	else
		put_text(l->gui, l->x_start + 80, l->cursor_y, "Test Grid");
	l->cursor_y += GUI_LINE_HEIGHT;
}
