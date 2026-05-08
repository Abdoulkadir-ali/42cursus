/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:23:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static bool	in_range(t_world *world, t_entity *ent)
{
	float	dx;
	float	dy;

	dx = ent->pos.x - world->player.render_pos.x;
	dy = ent->pos.y - world->player.render_pos.y;
	return (sqrtf(dx * dx + dy * dy) < 0.8f);
}

static void	pickup_medkit(t_world *world, t_entity *ent)
{
	if (world->player.health >= 100)
		return ;
	world->player.health += 25;
	if (world->player.health > 100)
		world->player.health = 100;
	ent->active = false;
}

static void	pickup_ammo(t_world *world, t_entity *ent)
{
	world->player.weapon_state.ammo[0] += 15 + rand() % 15;
	ent->active = false;
}

static void	pickup_shield(t_world *world, t_entity *ent)
{
	if (world->player.armor >= 100)
		return ;
	world->player.armor += 50;
	if (world->player.armor > 100)
		world->player.armor = 100;
	ent->active = false;
}

void	tick_item(t_world *world, t_entity *ent)
{
	if (!in_range(world, ent))
		return ;
	if (ent->type == ENTITY_ITEM_MEDKIT)
		pickup_medkit(world, ent);
	else if (ent->type == ENTITY_ITEM_AMMO)
		pickup_ammo(world, ent);
	else if (ent->type == ENTITY_ITEM_SHIELD)
		pickup_shield(world, ent);
}
