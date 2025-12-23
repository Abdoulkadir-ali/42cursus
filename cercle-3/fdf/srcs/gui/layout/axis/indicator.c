/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indicator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:19:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_axis_indicator(t_gui *gui)
{
	t_vec2		center;
	t_axis_info	axes[3];
	int			i;

	if (!gui || !gui->window || !gui->camera)
		return ;
	center.x = gui->window->width - AXIS_SIZE - AXIS_MARGIN;
	center.y = gui->window->height - AXIS_SIZE - AXIS_MARGIN;
	axes[0] = (t_axis_info){create_vec3d(1.0, 0.0, 0.0), 0xFF0000, 'X'};
	axes[1] = (t_axis_info){create_vec3d(0.0, 1.0, 0.0), 0x00FF00, 'Y'};
	axes[2] = (t_axis_info){create_vec3d(0.0, 0.0, 1.0), 0x0000FF, 'Z'};
	i = 0;
	while (i < 3)
	{
		draw_axis_line(gui, center, axes[i].axis, axes[i].color);
		i++;
	}
	draw_axis_labels(gui, center);
}
