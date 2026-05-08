/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	damage_player(t_world *world, int damage)
{
	int	armor_damage;
	int	health_damage;

	armor_damage = damage / 2;
	health_damage = damage - armor_damage;
	if (world->player.armor > 0)
	{
		if (armor_damage > world->player.armor)
		{
			health_damage += (armor_damage - world->player.armor);
			armor_damage = world->player.armor;
		}
		world->player.armor -= armor_damage;
	}
	else
		health_damage = damage;
	world->player.health -= health_damage;
	if (world->player.health < 0)
		world->player.health = 0;
}
