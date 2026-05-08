/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:32:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

bool	pf_has_path(const t_map *m, t_vec2 start, t_vec2 goal, bool dw)
{
	t_pathfinder_params	p;

	p.start = start;
	p.goal = goal;
	p.doors_are_walls = dw;
	p.next_step = NULL;
	return (pf_search(m, p, false));
}
