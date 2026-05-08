/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:26:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	drop_loot(t_world *world, t_vec2 pos)
{
	int	r;

	r = rand() % 100;
	if (r < 40)
		spawn_entity(world, ENTITY_ITEM_AMMO, pos);
	else if (r < 70)
		spawn_entity(world, ENTITY_ITEM_MEDKIT, pos);
	else if (r < 85)
		spawn_entity(world, ENTITY_ITEM_SHIELD, pos);
}
