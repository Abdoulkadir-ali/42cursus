/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:09:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"


/*
** Prints position and velocity of all dynamic spheres.
** Called once per physics frame when DEBUG is enabled.
*/
void	phys_debug_spheres(t_scene *scene)
{
	int			i;
	t_sphere	*sp;

	i = 0;
	while (i < scene->sphere_count)
	{
		sp = &scene->spheres[i];
		if (!sp->phys.is_static)
		{
			ft_print_debug("  Sp[%d] pos=(%.2f,%.2f,%.2f) "
				"vel=(%.2f,%.2f,%.2f) "
				"ang=(%.2f,%.2f,%.2f) "
				"r=%.2f deform=%d\n",
				i,
				sp->transform.pos.x, sp->transform.pos.y,
				sp->transform.pos.z,
				sp->phys.velocity.x, sp->phys.velocity.y,
				sp->phys.velocity.z,
				sp->phys.angular_velocity.x,
				sp->phys.angular_velocity.y,
				sp->phys.angular_velocity.z,
				sqrt(sp->radius_sq),
				sp->is_deformed);
		}
		i++;
	}
}
