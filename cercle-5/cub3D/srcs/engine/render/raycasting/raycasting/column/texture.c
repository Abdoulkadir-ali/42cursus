/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 22:27:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "physics.h"

t_texture	*get_render_texture(t_render_col *rc)
{
	return (&rc->world->map->textures[rc->dda->tex_idx]);
}

float	get_wall_x(t_render_col *rc)
{
	float	wall_x;

	if (rc->dda->side == 0)
		wall_x = rc->dda->hit_pos.y;
	else
		wall_x = rc->dda->hit_pos.x;
	wall_x -= floorf(wall_x);
	return (wall_x);
}
