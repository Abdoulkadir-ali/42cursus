/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:22:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <stdlib.h>

void	simulate_physics(t_physics *phys, double dt)
{
	if (phys == NULL)
		return ;
	if (phys->needs_bake || (phys->scene
			&& phys->baked_version != phys->scene->version))
	{
		phys_bake_scene(phys, phys->scene);
		if (phys->scene)
			phys->baked_version = phys->scene->version;
		phys->needs_bake = false;
	}
	update_physics(phys, dt);
}

void	physics_destroy(t_physics *phys)
{
	if (phys)
		phys_destroy(phys);
}
