/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:16:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_toggle_options(t_layout *l, t_gui *gui, char *buffer)
{
	if (gui->camera->use_z_divisor)
		gui_layout_key_value(l, "Z-Divisor (X):", "ON");
	else
		gui_layout_key_value(l, "Z-Divisor (X):", "OFF");
	if (gui->camera->invert_movement)
		gui_layout_key_value(l, "Invert Move (I):", "Camera");
	else
		gui_layout_key_value(l, "Invert Move (I):", "Object");
	if (gui->render_config->use_horizon_culling)
		gui_layout_key_value(l, "Ray Cast (J):", "ON");
	else
		gui_layout_key_value(l, "Ray Cast (J):", "OFF");
	if (!gui->render_config->use_adaptive_logic)
	{
		if (gui->render_config->lod_value > 1.01f)
			format_float(gui->render_config->lod_value, buffer);
		else
			ft_strcpy(buffer, "1.0");
		gui_layout_key_value(l, "Manual LOD (Hm/End):", buffer);
	}
}
