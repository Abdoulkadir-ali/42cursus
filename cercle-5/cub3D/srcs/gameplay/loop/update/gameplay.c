/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:31:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	update_gameplay(t_world *world, int elapsed_us)
{
	bool	shot;
	bool	reload;
	int		prev_rld;

	if (world == NULL || world->map == NULL)
		return ;
	update_fps(world, elapsed_us);
	shot = world->player.controller.input.shoot != 0;
	reload = false;
	apply_action_flags(world, elapsed_us);
	if (world->player.weapon_state.cooldown > 0)
		world->player.weapon_state.cooldown--;
	handle_weapon_update(world, &shot, &reload);
	prev_rld = world->weapon_anim.reloading;
	tick_anim(world, shot, reload, elapsed_us);
	update_debug_shapes(world, elapsed_us);
	if (prev_rld != 0 && world->weapon_anim.reloading == 0)
		set_reload_ammo(&world->player.weapon_state);
	world->player.controller.input.shoot = 0;
	world->player.controller.input.reload = 0;
	update_door_animations(world, elapsed_us);
	tick_entities(world, elapsed_us);
}
