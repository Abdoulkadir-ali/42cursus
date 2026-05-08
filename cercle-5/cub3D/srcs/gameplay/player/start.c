/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:34:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:51:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	set_player_start(t_player *player, char dir)
{
	if (dir == 'N')
		player->actor.dir = (t_vec3){0.0f, -1.0f, 0.0f};
	else if (dir == 'S')
		player->actor.dir = (t_vec3){0.0f, 1.0f, 0.0f};
	else if (dir == 'E')
		player->actor.dir = (t_vec3){1.0f, 0.0f, 0.0f};
	else
		player->actor.dir = (t_vec3){-1.0f, 0.0f, 0.0f};
}

void	init_player_from_map(t_player *player, t_map *map)
{
	if (player == NULL || map == NULL)
		return ;
	player->actor.pos.x = map->player_spawn.pos.x;
	player->actor.pos.y = map->player_spawn.pos.y;
	player->actor.pos.z = 0.0f;
	set_player_start(player, map->player_spawn.dir);
	player->actor.speed = 2.0f;
	player->pitch_offset = 0.0f;
	player->render_pos = player->actor.pos;
	player->render_dir = player->actor.dir;
	player->render_pitch_offset = player->pitch_offset;
	player->health = 100;
	player->weapon_state.type = WEAPON_PISTOL;
	player->weapon_state.has_weapon = 1;
	player->weapon_state.ammo[WEAPON_PISTOL] = 12;
	player->weapon_state.ammo[WEAPON_MELEE] = 1;
	player->weapon_state.ammo[WEAPON_PROJECTILE] = 5;
	player->weapon_state.cooldown = 0;
	player->fov = 90.0f;
	player->pos_z = 0.0f;
	player->vel_z = 0.0f;
	player->render_pos_z = 0.0f;
	player->controller.player = player;
	player->controller.input = (t_player_input){0};
	player->controller.mouse = (t_mouse){0};
}
