/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impact.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:52:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

void	calculate_impact(t_world *world, t_vec2 ray, float dist, t_vec3 *impact)
{
	impact->x = world->player.render_pos.x + ray.x * dist;
	impact->y = world->player.render_pos.y + ray.y * dist;
	impact->z = world->player.render_pos.z + world->player.render_pitch_offset
		* dist;
}
