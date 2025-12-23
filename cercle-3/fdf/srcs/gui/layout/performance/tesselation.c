/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:41:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:41:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	format_detail_level(int level, char *buffer)
{
	char	*type_str;

	if (level > 0)
	{
		type_str = " (TESS)";
		buffer[0] = '+';
		format_number(level, buffer + 1);
	}
	else
	{
		if (level < 0)
			type_str = " (LOD)";
		else
			type_str = " (BASE)";
		format_number(level, buffer);
	}
	ft_strlcat(buffer, type_str, 50);
}

void	display_tesselation_info(t_layout *l, t_gui *gui, char *buffer)
{
	int	level;

	level = gui->render_config->detail_level;
	format_detail_level(level, buffer);
	gui_layout_key_value(l, "Detail Level:", buffer);
	if (gui->render_config->use_adaptive_logic)
		gui_layout_key_value(l, "Mode (M):", "AUTO");
	else
		gui_layout_key_value(l, "Mode (M):", "MANUAL");
	format_number((long long)gui->render_config->target_tesselation_points,
		buffer);
	gui_layout_key_value(l, "Target Pts (B+/-):", buffer);
}
