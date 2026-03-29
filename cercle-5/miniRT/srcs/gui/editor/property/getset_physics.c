/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_physics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:20:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"
#include "physics.h"

double	get_ph_mass(t_scene *sc, int i)
{
	if (!sc->phys || (size_t)i >= sc->phys->soa->count)
		return (0);
	return (sc->phys->soa->mass[i]);
}

void	set_ph_mass(t_scene *sc, int i, double v)
{
	if (!sc->phys || (size_t)i >= sc->phys->soa->count)
		return ;
	sc->phys->soa->mass[i] = v;
	sc->phys->needs_bake = true;
	scene_mark_dirty(sc);
}

double	get_ph_elast(t_scene *sc, int i)
{
	if (!sc->phys || (size_t)i >= sc->phys->soa->count)
		return (0);
	return (sc->phys->soa->elasticity[i]);
}

void	set_ph_elast(t_scene *sc, int i, double v)
{
	if (!sc->phys || (size_t)i >= sc->phys->soa->count)
		return ;
	sc->phys->soa->elasticity[i] = v;
	sc->phys->needs_bake = true;
	scene_mark_dirty(sc);
}

double	get_ph_fric(t_scene *sc, int i)
{
	if (!sc->phys || (size_t)i >= sc->phys->soa->count)
		return (0);
	return (sc->phys->soa->friction[i]);
}
