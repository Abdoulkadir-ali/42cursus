/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:36:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

void	update_door_animations(t_world *world, int elapsed_us)
{
	int	i;

	i = 0;
	while (i < MAX_ACTIVE_DOORS)
	{
		if (world->active_doors[i].active)
			tick_door(world, i, elapsed_us);
		i++;
	}
}
