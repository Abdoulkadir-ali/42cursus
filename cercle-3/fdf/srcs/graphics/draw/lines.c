/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:44:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "graphics.h"
#include "vectors.h"

static void	init_bresenham(t_bresenham *b, t_point s, t_point e)
{
	t_vec2	delta;

	delta.x = e.pos.x - s.pos.x;
	delta.y = e.pos.y - s.pos.y;
	b->delta.x = abs(delta.x);
	b->delta.y = abs(delta.y);
	if (delta.x >= 0)
		b->step.x = 1;
	else
		b->step.x = -1;
	if (delta.y >= 0)
		b->step.y = 1;
	else
		b->step.y = -1;
	b->err = b->delta.x - b->delta.y;
	b->p.x = s.pos.x;
	b->p.y = s.pos.y;
}

static void	init_line_state(t_line_draw_state *state, t_graphics *g,
		t_point start, t_point end)
{
	state->s_pos.x = start.pos.x;
	state->s_pos.y = start.pos.y;
	state->e_pos.x = end.pos.x;
	state->e_pos.y = end.pos.y;
	state->delta_total = state->e_pos;
	vec2d_sub(&state->delta_total, state->s_pos);
	state->total_dist = vec2d_len(state->delta_total);
	state->c = g->camera;
	init_bresenham(&state->b, start, end);
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	t_line_draw_state state;

	init_line_state(&state, g, start, end);
	while (1)
	{
		if (is_visible(state.b.p.x, state.b.p.y, g))
		{
			calculate_color(&state, start, end);
			img_pixel_put_with_z(g, state.b.p.x, state.b.p.y, 0.0, state.color);
		}
		if (state.b.p.x == end.pos.x && state.b.p.y == end.pos.y)
			break ;
		state.b.e2 = 2 * state.b.err;
		if (state.b.e2 > -state.b.delta.y)
		{
			state.b.err -= state.b.delta.y;
			state.b.p.x += state.b.step.x;
		}
		if (state.b.e2 < state.b.delta.x)
		{
			state.b.err += state.b.delta.x;
			state.b.p.y += state.b.step.y;
		}
	}
}