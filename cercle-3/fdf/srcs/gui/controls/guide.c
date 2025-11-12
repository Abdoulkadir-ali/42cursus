/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:46:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:33:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "data.h"

void	draw_controls_guide_at(t_data *data, int *section_y)
{
	int	y;

	y = *section_y;
	put_colored(data, (t_vec2){GUI_PADDING, y}, "CONTROLS", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	draw_mouse_controls(data, &y);
	draw_keyboard_controls(data, &y);
	draw_action_keys(data, &y);
	draw_optimization_keys(data, &y);
	*section_y = y;
}
