/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:39:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_rot_stats(t_layout *l, t_gui *gui, char *buffer)
{
	t_vec3	v;

	v = (t_vec3){normalize_angle(gui->camera->rotation.x),
		normalize_angle(gui->camera->rotation.y),
		normalize_angle(gui->camera->rotation.z)};
	format_number(v.x, buffer);
	gui_layout_key_value(l, "Rot X (deg):", buffer);
	format_number(v.y, buffer);
	gui_layout_key_value(l, "Rot Y (deg):", buffer);
	format_number(v.z, buffer);
	gui_layout_key_value(l, "Rot Z (deg):", buffer);
}
