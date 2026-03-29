/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_physics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 01:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 15:08:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "debug.h"

void	debug_print_physics_state(t_physics *phys)
{
	size_t				i;
	t_physics_soa		*p;
	t_primitive_array	*gm;

	if (!phys || !phys->scene || !phys->soa)
		return ;
	p = phys->soa;
	gm = &phys->scene->primitives;
	i = 0;
	while (i < p->count)
	{
		if (!p->is_static[i])
		{
			DBG_INFO_MSG(DBG_CH_PHYSICS, "[PHYS] Body %zu (prim %d): y=%.3f, vy=%.3f\n",
				i, p->prim_idx[i], gm->py[p->prim_idx[i]], p->hot.vy[i]);
		}
		i++;
	}
}