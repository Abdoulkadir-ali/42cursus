/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:37:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:34:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	render_single_entity(t_window *win, t_world *world, t_entity *ent)
{
	t_vec2				transform;
	t_spr_draw_params	params;
	t_spr_draw			sd;

	calc_sprite_pos(win, world, ent, &transform);
	if (transform.y <= 0.0f)
		return ;
	params.win = win;
	params.world = world;
	params.ent = ent;
	params.transform = transform;
	params.sx = (int)((win->width / 2) * (1 + transform.x / transform.y));
	sd = make_spr_draw(params);
	draw_sprite(win, ent, transform, &sd);
}

void	render_entities(t_window *win, t_world *world)
{
	size_t	indices[MAX_ENTITIES];
	float	distances[MAX_ENTITIES];
	size_t	i;

	if (world->entity_count == 0)
		return ;
	sort_entities(world, indices, distances);
	i = 0;
	while (i < world->entity_count)
	{
		if (world->entities[indices[i]].active
			&& world->entities[indices[i]].clip)
			render_single_entity(win, world, &world->entities[indices[i]]);
		i++;
	}
}
