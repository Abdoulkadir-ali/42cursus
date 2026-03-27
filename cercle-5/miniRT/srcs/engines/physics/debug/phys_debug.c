/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified DOD debug report for all dynamic primitives.
 * Iterates through the primitive SoA and prints physics body state.
 */
void	phys_debug_spheres(t_scene *scene)
{
	size_t				i;
	t_primitive_array	*p;
	t_physics_body		*b;

	if (scene == NULL)
		return ;
	p = &scene->primitives;
	i = 0;
	ft_print_debug("--- Physics State Report ---\n");
	while (i < p->count)
	{
		b = p->physics[i];
		if (b != NULL && !b->is_static)
		{
			ft_print_debug("  Prim[%zu] type=%d pos=(%.2f,%.2f,%.2f) "
				"vel=(%.2f,%.2f,%.2f) ang_vel=(%.2f,%.2f,%.2f)\n",
				i, (int)p->types[i], (double)p->px[i], (double)p->py[i],
				(double)p->pz[i], b->velocity.x, b->velocity.y, b->velocity.z,
				b->angular_velocity.x, b->angular_velocity.y,
				b->angular_velocity.z);
		}
		i++;
	}
}
