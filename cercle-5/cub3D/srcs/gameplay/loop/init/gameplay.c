/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:00:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:31:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "exit.h"
#include "gameplay.h"

static void	init_weapon_state(t_world *world, t_window *window)
{
	t_weapon_state	*ws;

	ws = &world->player.weapon_state;
	init_pistol(&world->weapon_anim, window, world);
	ws->type = WEAPON_PISTOL;
	ws->has_weapon = 1;
	ws->ammo[WEAPON_PISTOL] = get_weapon_max_ammo(WEAPON_PISTOL);
	ws->ammo[WEAPON_MELEE] = get_weapon_max_ammo(WEAPON_MELEE);
	ws->ammo[WEAPON_PROJECTILE] = get_weapon_max_ammo(WEAPON_PROJECTILE);
}

static void	spawn_debug_enemy(t_world *world)
{
	t_vec2	spawn_pos;
	float	offset;

	if (world->entity_count > 0)
		return ;
	offset = 2.0f;
	spawn_pos.x = world->player.actor.pos.x + world->player.actor.dir.x
		* offset;
	spawn_pos.y = world->player.actor.pos.y + world->player.actor.dir.y
		* offset;
	if (!is_wall(world, (t_vec3){spawn_pos.x, spawn_pos.y, 0.0f}))
		spawn_entity(world, ENTITY_ENEMY_GUARD, spawn_pos);
}

void	init_gameplay(t_world *world, t_window *window, char *map_file,
		t_app *app)
{
	t_map	tmp_map;

	ft_memset(world, 0, sizeof(t_world));
	if (!parse_map(map_file, &tmp_map))
		safe_exit("Failed to parse map", app, 1);
	init_gameplay_maps(world, &tmp_map);
	if (!load_map_textures(world->map, world, app))
		safe_exit("Failed to load texture", app, 1);
	init_player_from_map(&world->player, world->map);
	init_weapon_state(world, window);
	init_gameplay_assets(world, window, app);
	init_entities(world);
	spawn_debug_enemy(world);
}
