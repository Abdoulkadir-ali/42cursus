/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:38:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 04:48:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimization.h"

void	init_optimization(t_world *world)
{
	if (world == NULL)
		return ;
	world->player.render_pos = world->player.actor.pos;
	world->player.render_dir = world->player.actor.dir;
	world->player.render_pitch_offset = world->player.pitch_offset;
	world->player.render_pos_z = world->player.pos_z;
}

void	update_optimization(t_world *world, int elapsed_us)
{
	(void)elapsed_us;
	if (world == NULL)
		return ;
	world->player.render_pos = world->player.actor.pos;
	world->player.render_dir = normalize_vec3(world->player.actor.dir);
	world->player.render_pitch_offset = world->player.pitch_offset;
	world->player.render_pos_z = world->player.pos_z;
}
