/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Global integration loop. 
 * Orchestrates objects through the Chef de Gare (dispatcher).
 * Compound bodies use the AAA path; primitives use Legacy integrators.
 */
void	integrate_bodies(t_scene *scene, double dt)
{
	int	i;

	if (!scene)
		return ;
	i = -1;
	while (++i < scene->sphere_count)
	{
		if (scene->spheres[i].phys.is_compound)
			phys_dispatch_object(&scene->spheres[i].phys, &scene->spheres[i].transform, dt);
		else
			integrate_sphere(&scene->spheres[i], dt);
	}
	i = -1;
	while (++i < scene->box_count)
	{
		if (scene->boxes[i].phys.is_compound)
			phys_dispatch_object(&scene->boxes[i].phys, &scene->boxes[i].transform, dt);
		else
			integrate_box(&scene->boxes[i], dt);
	}
	i = -1;
	while (++i < scene->capsule_count)
	{
		if (scene->capsules[i].phys.is_compound)
			phys_dispatch_object(&scene->capsules[i].phys, &scene->capsules[i].transform, dt);
		else
			integrate_capsule(&scene->capsules[i], dt);
	}
	i = -1;
	while (++i < scene->cylinder_count)
	{
		if (scene->cylinders[i].phys.is_compound)
			phys_dispatch_object(&scene->cylinders[i].phys, &scene->cylinders[i].transform, dt);
		else
			integrate_cylinder(&scene->cylinders[i], dt);
	}
}
