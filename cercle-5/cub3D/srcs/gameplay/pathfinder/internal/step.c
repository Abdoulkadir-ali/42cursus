/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:32:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

void	pf_step_reconstruct(t_pf_search *s, t_vec2 *next_step)
{
	size_t	si;
	size_t	st_idx;

	si = s->goal_idx;
	st_idx = (size_t)s->start.y * s->width + (size_t)s->start.x;
	while (si != st_idx && (size_t)s->prev[si] != st_idx)
		si = (size_t)s->prev[si];
	next_step->x = (float)(si % s->width) + 0.5f;
	next_step->y = (float)(si / s->width) + 0.5f;
}
