/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 05:16:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:51:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

int	get_weapon_max_ammo(int type)
{
	if (type == WEAPON_PISTOL)
		return (12);
	if (type == WEAPON_MELEE)
		return (1);
	if (type == WEAPON_PROJECTILE)
		return (5);
	return (0);
}

int	get_weapon_fire_cooldown(int type)
{
	if (type == WEAPON_PISTOL)
		return (5);
	if (type == WEAPON_MELEE)
		return (15);
	if (type == WEAPON_PROJECTILE)
		return (25);
	return (0);
}

void	set_reload_ammo(t_weapon_state *state)
{
	int	max_ammo;

	if (state == NULL)
		return ;
	max_ammo = get_weapon_max_ammo(state->type);
	state->ammo[state->type] = max_ammo;
}

float	get_wall_x_dda(t_dda *d, t_world *world, t_vec2 ray)
{
	float	wall_x;

	if (d->side == 0)
		wall_x = world->player.render_pos.y + d->perp_dist * ray.y;
	else
		wall_x = world->player.render_pos.x + d->perp_dist * ray.x;
	wall_x -= floorf(wall_x);
	return (wall_x);
}

bool	check_door_pixel(t_world *world, int door_idx, t_dda *d, t_vec2 ray)
{
	t_anim_clip	*clip;
	t_texture	tex;
	float		wall_x;
	int			tx;

	clip = world->door_open_clip;
	if (world->active_doors[door_idx].type == 2)
		clip = world->door_close_clip;
	if (!clip)
		return (false);
	tex.data = clip->frames[world->active_doors[door_idx].state.frame];
	tex.size = clip->size;
	wall_x = get_wall_x_dda(d, world, ray);
	tx = (int)(wall_x * (float)tex.size.x);
	if ((d->side == 0 && d->step_x > 0) || (d->side == 1 && d->step_y < 0))
		tx = (int)tex.size.x - tx - 1;
	if (tx < 0)
		tx = 0;
	if ((size_t)tx >= tex.size.x)
		tx = (int)tex.size.x - 1;
	return (tex.data[tx] >> 24 == 0);
}
