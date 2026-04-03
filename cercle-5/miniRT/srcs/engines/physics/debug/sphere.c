/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:51:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** Prints position and velocity of all dynamic spheres.
** Called once per physics frame when DEBUG is enabled.
*/
void	phys_debug_spheres(t_scene *scene)
{
	size_t		i;
	t_sphere	*sp;

	i = 0;
	while (i < scene->sphere_count)
	{
		sp = &scene->spheres[i];
		if (!sp->phys.is_static)
		{
			ft_print_debug("  Sp[%zu] pos=(%.2f,%.2f,%.2f) "
				"vel=(%.2f,%.2f,%.2f) "
				"r=%.2f\n",
				i,
				sp->phys.pos.x, sp->phys.pos.y,
				sp->phys.pos.z,
				sp->phys.velocity.x, sp->phys.velocity.y,
				sp->phys.velocity.z,
				sqrt(sp->radius_sq));
		}
		i++;
	}
}
