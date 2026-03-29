/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_physics_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:20:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"
#include "physics.h"

void	set_ph_fric(t_scene *sc, int i, double v)
{
	if (!sc->phys || (size_t)i >= sc->phys->soa->count)
		return ;
	sc->phys->soa->friction[i] = v;
	sc->phys->needs_bake = true;
	scene_mark_dirty(sc);
}
