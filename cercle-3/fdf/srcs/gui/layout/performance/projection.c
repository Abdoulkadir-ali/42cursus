/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:34:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_projection_display_layout(t_layout *l, t_gui *gui)
{
	char	*names[PROJ_COUNT];
	char	buffer[20];
	char	*label;

	names[0] = "PARALLEL";
	names[1] = "CONIC";
	gui_layout_title(l, "MODE");
	gui_layout_key_value(l, "Type (P):", names[gui->camera->projection]);
	if (gui->camera->projection == PROJ_PARALLEL)
		label = "Incidence (A):";
	else
		label = "FOV (A):";
	format_number((int)gui->camera->alpha, buffer);
	gui_layout_key_value(l, label, buffer);
}
