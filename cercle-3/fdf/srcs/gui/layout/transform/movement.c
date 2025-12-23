/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:33:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_speed_display_layout(t_layout *l, t_gui *gui)
{
	char	move_str[10];
	char	zoom_str[10];
	char	rot_str[10];

	gui_layout_title(l, "SPEEDS");
	format_speed(gui->camera->move_speed, move_str);
	gui_layout_key_value(l, "Move:", move_str);
	format_speed(gui->camera->zoom_speed, zoom_str);
	gui_layout_key_value(l, "Zoom:", zoom_str);
	format_speed(gui->camera->rotation_speed / DEFAULT_ROTATION_SPEED, rot_str);
	gui_layout_key_value(l, "Rotation:", rot_str);
}
