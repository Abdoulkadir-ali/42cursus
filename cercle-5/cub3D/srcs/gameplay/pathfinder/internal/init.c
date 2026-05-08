/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 23:43:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

static void	pf_init_params(t_pf_search *s, const t_map *m, t_vec2i start,
		t_vec2i goal)
{
	s->width = m->width;
	s->height = m->height;
	s->area = s->width * s->height;
	s->start = start;
	s->goal = goal;
	s->start_idx = (size_t)s->start.y * s->width + (size_t)s->start.x;
	s->goal_idx = (size_t)s->goal.y * s->width + (size_t)s->goal.x;
	s->qi = 0;
	s->qj = 0;
}

bool	pf_init_state(t_pf_search *s, const t_map *m, t_vec2i start,
		t_vec2i goal)
{
	pf_init_params(s, m, start, goal);
	s->prev = malloc(sizeof(int) * s->area);
	s->queue = malloc(sizeof(int) * s->area);
	if (!s->prev || !s->queue)
	{
		free(s->prev);
		free(s->queue);
		return (false);
	}
	ft_memset(s->prev, -1, sizeof(int) * s->area);
	s->queue[s->qj++] = (int)s->start_idx;
	s->prev[s->start_idx] = (int)s->start_idx;
	return (true);
}
