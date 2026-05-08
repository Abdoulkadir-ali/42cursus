/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:31:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "engine.h"

static void	trigger_reload(t_world *world)
{
	if (world->weapon_anim.reloading == 0)
	{
		world->weapon_anim.reloading = 1;
		anim_set_active_clip(&world->weapon_anim,
			world->weapon_anim.clips.reload, 5, 0);
	}
}

bool	handle_shooting(t_world *world, bool fired)
{
	t_weapon_state	*ws;

	ws = &world->player.weapon_state;
	if (!fired || world->weapon_anim.reloading != 0)
		return (false);
	if (ws->cooldown <= 0)
	{
		if (ws->type == WEAPON_MELEE || ws->ammo[ws->type] > 0)
		{
			if (ws->type != WEAPON_MELEE)
				ws->ammo[ws->type]--;
			ws->cooldown = get_weapon_fire_cooldown(ws->type);
			fire_weapon(world);
			return (true);
		}
		trigger_reload(world);
	}
	return (false);
}

void	handle_weapon_update(t_world *world, bool *shot, bool *reload)
{
	int	type;

	if (world->player.weapon_state.has_weapon != 0
		&& world->player.weapon_state.type != WEAPON_NONE)
	{
		*shot = handle_shooting(world, *shot);
		type = world->player.weapon_state.type;
		if (world->player.controller.input.reload != false
			&& world->weapon_anim.reloading == 0
			&& world->player.weapon_state.ammo[type]
			< get_weapon_max_ammo(type))
			*reload = true;
	}
}
