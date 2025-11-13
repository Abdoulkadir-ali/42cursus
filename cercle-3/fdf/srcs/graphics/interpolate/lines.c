/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:22:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:32:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	calculate_color(t_line_draw_state *state, t_point start, t_point end)
{
	state->current_pos.x = state->b.p.x;
	state->current_pos.y = state->b.p.y;
	state->delta_current = state->current_pos;
	vec2d_sub(&state->delta_current, state->s_pos);
	state->current_dist = vec2d_len(state->delta_current);
	if (state->total_dist == 0.0)
		state->total_dist = 1e-6;
	state->color = interpolate_color(start.color, end.color, state->current_dist
			/ state->total_dist);
	state->color = shift_color(state->color, state->c->color_shift.x,
			state->c->color_shift.z, state->c->color_shift.y);
}