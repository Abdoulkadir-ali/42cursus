/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/14 16:29:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "graphics.h"
#include "vectors.h"
#include <execinfo.h>
#include <stdlib.h>
#include <string.h>

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
	/* diagnostic: ensure Bresenham start point is initialized */
	printf("[diag] init_bresenham: start p=(%d,%d)\n", b->p.x, b->p.y);
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
	volatile unsigned int stack_canary = 0xDEADBEEF;
	unsigned char *state_bytes;
	int state_size;
	unsigned char *saved_state = NULL;
	size_t b_offset = 0;
	size_t b_size = 0;

	printf("[diag] draw_line start=(%d,%d) end=(%d,%d)\n",
		(int)start.pos.x, (int)start.pos.y, (int)end.pos.x, (int)end.pos.y);
	if (abs((int)end.pos.x - (int)start.pos.x) > 10000 || abs((int)end.pos.y - (int)start.pos.y) > 10000)
	{
		printf("[diag] draw_line: coords out of range, skipping\n");
		return ;
	}
	init_line_state(&state, g, start, end);
	/* save snapshot of state except the Bresenham sub-struct (it will be mutated) */
	state_size = (int)sizeof(state);
	saved_state = malloc((size_t)state_size);
	if (saved_state)
	{
		memcpy(saved_state, &state, (size_t)state_size);
		b_offset = (unsigned char *)&state.b - (unsigned char *)&state;
		b_size = sizeof(state.b);
	}
	printf("[diag] draw_line stack_canary addr=%p val=0x%08x\n", (void *)&stack_canary, (unsigned int)stack_canary);
	/* dump initial bytes of state for later comparison */
	state_bytes = (unsigned char *)&state;
	state_size = (int)sizeof(state);
	printf("[diag] state addr=%p size=%d b.addr=%p b.p.addr=%p\n", (void *)&state, state_size, (void *)&state.b, (void *)&state.b.p);
	printf("[diag] state first 32 bytes:");
	for (int i = 0; i < 32 && i < state_size; ++i)
		printf(" %02x", state_bytes[i]);
	printf("\n");
	int iter = 0;
	while (1)
	{
		/* periodically check for unexpected modifications to 'state' */
		if (saved_state && iter % 20 == 0)
		{
			unsigned char *cur = (unsigned char *)&state;
			for (int k = 0; k < state_size; ++k)
			{
				if ((size_t)k >= b_offset && (size_t)k < b_offset + b_size)
					continue; /* expected to change */
				if (cur[k] != saved_state[k])
				{
					printf("[diag] UNEXPECTED WRITE detected in draw_line at iter=%d offset=%d\n", iter, k);
					printf("[diag] old byte=%02x new byte=%02x\n", saved_state[k], cur[k]);
					void *bt[32];
					int bt_size = backtrace(bt, 32);
					char **bt_syms = backtrace_symbols(bt, bt_size);
					if (bt_syms)
					{
						printf("[diag] backtrace (most recent first):\n");
						for (int i = 0; i < bt_size; ++i)
							printf("  %s\n", bt_syms[i]);
						free(bt_syms);
					}
					free(saved_state);
					saved_state = NULL;
					return ;
				}
			}
		}
		if (iter < 5)
			printf("[diag] draw_line iter=%d p=(%d,%d) end=(%f,%f)\n", iter, state.b.p.x, state.b.p.y, state.e_pos.x, state.e_pos.y);
		if (iter % 50 == 0)
		{
				/* dump bytes around b.p safely (stay inside 'state' bounds) */
				unsigned char *base = (unsigned char *)&state;
				size_t base_size = (size_t)state_size;
				size_t bpoff = (unsigned char *)&state.b.p - base;
				printf("[diag] dump around state.b.p:");
				for (int j = -8; j < 8; ++j)
				{
					long idx = (long)bpoff + j;
					if (idx >= 0 && (size_t)idx < base_size)
						printf(" %02x", base[idx]);
					else
						printf(" --");
				}
				printf("\n");
		}
		iter++;
		if (is_visible(state.b.p.x, state.b.p.y, g))
		{
			calculate_color(&state, start, end);
			img_pixel_put_with_z(g, state.b.p.x, state.b.p.y, 0.0, state.color);
			if (stack_canary != 0xDEADBEEF)
			{
				printf("[diag] STACK CORRUPTION detected! canary=0x%08x addr=%p\n",
					(unsigned int)stack_canary, (void *)&stack_canary);
				return ;
			}
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