/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:33:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 23:52:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	init_mouse_hook(t_window *window, t_player_controller *controller)
{
	controller->mouse.lmb_pressed = 0;
	controller->mouse.prev_x = 0;
	controller->mouse.prev_y = 0;
	mlx_hook(window->win, 4, 1L << 2, (void *)handle_mouse_press, controller);
	mlx_hook(window->win, 5, 1L << 3, (void *)handle_mouse_release, controller);
	mlx_hook(window->win, 6, 1L << 6, (void *)handle_mouse_motion, controller);
}
