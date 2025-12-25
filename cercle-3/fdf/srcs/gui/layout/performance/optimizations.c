/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:22:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_toggle_options(t_layout *l, t_gui *gui, char *buffer)
{
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
	}
}
