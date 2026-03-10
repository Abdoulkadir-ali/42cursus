/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Reset the mouse state structure to its default released state.
 * @param mouse Mouse state structure to initialize.
 */
void	init_mouse(t_mouse *mouse)
{
	mouse->left_pressed = 0;
	mouse->right_pressed = 0;
	mouse->middle_pressed = 0;
	mouse->last_x = 0;
	mouse->last_y = 0;
	mouse->middle_start_x = 0;
	mouse->middle_start_y = 0;
}
