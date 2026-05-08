/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:03:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

static void	pf_try_enqueue(t_pf_search *s, const t_map *m, t_vec2i n, bool dw)
{
	size_t	ni;

	if (n.x >= 0 && n.y >= 0 && (size_t)n.x < s->width
		&& (size_t)n.y < s->height)
	{
		ni = (size_t)n.y * s->width + (size_t)n.x;
		if (s->prev[ni] == -1 && pf_is_tile_passable(m, n, dw))
		{
			s->prev[ni] = s->queue[s->qi];
			s->queue[s->qj++] = (int)ni;
		}
	}
}

static void	pf_explore(t_pf_search *s, const t_map *map, bool doors_are_walls)
{
	static const t_vec2i	dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	t_vec2i					p;
	t_vec2i					n;
	int						di;

	p.x = s->queue[s->qi] % (int)s->width;
	p.y = s->queue[s->qi] / (int)s->width;
	di = -1;
	while (++di < 4)
	{
		n.x = p.x + dirs[di].x;
		n.y = p.y + dirs[di].y;
		pf_try_enqueue(s, map, n, doors_are_walls);
	}
	s->qi++;
}

static bool	pf_loop(t_pf_search *state, const t_map *m, bool dw)
{
	while (state->qi < state->qj)
	{
		if ((size_t)state->queue[state->qi] == state->goal_idx)
			return (true);
		pf_explore(state, m, dw);
	}
	return (false);
}

bool	pf_search(const t_map *map, t_pathfinder_params p, bool need_step)
{
	t_pf_search	st;
	t_vec2i		s;
	t_vec2i		g;
	bool		f;

	s = (t_vec2i){(int)floorf(p.start.x), (int)floorf(p.start.y)};
	g = (t_vec2i){(int)floorf(p.goal.x), (int)floorf(p.goal.y)};
	if (!pf_init_state(&st, map, s, g))
		return (false);
	f = pf_loop(&st, map, p.doors_are_walls);
	if (f && need_step)
		pf_step_reconstruct(&st, p.next_step);
	free(st.prev);
	free(st.queue);
	return (f);
}
