/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 03:15:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 20:38:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	init_player_controller(t_player_controller *controller,
		t_player *player)
{
	controller->player = player;
	controller->input = (t_player_input){0};
	controller->mouse = (t_mouse){0};
}

void	update_player_controller(t_player_controller *controller)
{
	(void)controller;
}
