/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:35:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 15:05:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	init_player(t_player *player)
{
	player->actor.pos = (t_vec3){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f,
		0.0f};
	player->actor.dir = (t_vec3){1.0f, 0.0f, 0.0f};
	player->actor.speed = 2.0f;
	player->pitch_offset = 0.0f;
	player->render_pos = player->actor.pos;
	player->render_dir = player->actor.dir;
	player->render_pitch_offset = player->pitch_offset;
	player->fov = 90.0f;
	player->health = 100;
	player->controller.player = player;
	player->controller.input = (t_player_input){0};
	player->controller.mouse = (t_mouse){0};
}
