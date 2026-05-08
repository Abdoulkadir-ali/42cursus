/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:37:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 07:37:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static float	get_entity_scale(const t_entity *ent)
{
	if (ent->type == ENTITY_ITEM_AMMO || ent->type == ENTITY_ITEM_MEDKIT
		|| ent->type == ENTITY_ITEM_SHIELD)
		return (0.20f);
	return (1.0f);
}

static int	calc_screen_y_offset(t_spr_draw_params p, int spr_h)
{
	int	joff;
	int	pitch;

	joff = (int)(p.world->player.render_pos_z * (float)p.win->height
			/ p.transform.y);
	pitch = (int)(p.world->player.render_pitch_offset
			* (float)p.win->height);
	return (p.win->height / 2 - spr_h / 2 - pitch + joff);
}

t_spr_draw	make_spr_draw(t_spr_draw_params params)
{
	t_spr_draw	sd;
	float		scale;

	scale = get_entity_scale(params.ent);
	sd.spr_sz.y = abs((int)((float)params.win->height / params.transform.y
				* scale));
	sd.spr_sz.x = sd.spr_sz.y;
	sd.start.x = params.sx;
	sd.map = params.world->map;
	sd.depth = params.transform.y;
	sd.dsy = calc_screen_y_offset(params, sd.spr_sz.y);
	sd.start.y = sd.dsy;
	return (sd);
}
