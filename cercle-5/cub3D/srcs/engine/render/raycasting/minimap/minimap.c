/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 21:58:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	set_start_pos(t_world *world, t_vec2i *st, int v_rad, int v_sz)
{
	st->x = (int)world->player.render_pos.x - v_rad;
	st->y = (int)world->player.render_pos.y - v_rad;
	if (st->x < 0)
		st->x = 0;
	if (st->y < 0)
		st->y = 0;
	if ((int)world->map->size.x > v_sz
		&& st->x + v_sz > (int)world->map->size.x)
		st->x = (int)world->map->size.x - v_sz;
	if ((int)world->map->size.y > v_sz
		&& st->y + v_sz > (int)world->map->size.y)
		st->y = (int)world->map->size.y - v_sz;
}

void	render_minimap(t_window *win, t_world *world)
{
	t_vec2i	st;
	int		v_rad;
	int		v_sz;

	if (world->map == NULL || world->map->grid == NULL)
		return ;
	v_rad = 15;
	v_sz = v_rad * 2 + 1;
	set_start_pos(world, &st, v_rad, v_sz);
	draw_minimap_grid(win, world, st, v_sz);
	draw_player_arrow(win, world, st.x, st.y);
}
