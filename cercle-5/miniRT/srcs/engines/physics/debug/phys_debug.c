/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:22:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified DOD debug report for all dynamic primitives.
 * Iterates through the primitive SoA and prints physics body state.
 */
void	phys_debug_spheres(t_physics *phys)
{
	size_t			i;
	t_primitive_array	*p;
	t_physics_soa		*soa;

	if (phys == NULL || phys->scene == NULL)
		return ;
	p = &phys->scene->primitives;
	soa = phys->soa;
	i = 0;
	ft_print_debug("--- Physics State Report ---\n");
	while (i < p->count)
	{
		if (soa && (int)i < (int)soa->count)
			ft_print_debug("  Prim[%zu] type=%d pos=(%.2f,%.2f,%.2f)\n",
				i, (int)p->types[i],
				(double)p->px[i], (double)p->py[i], (double)p->pz[i]);
		i++;
	}
}
