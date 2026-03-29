/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_lights_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_lt_py(t_scene *sc, int i)
{
	return (sc->lights[i].transform.pos.y);
}

void	set_lt_py(t_scene *sc, int i, double v)
{
	sc->lights[i].transform.pos.y = v;
	scene_mark_dirty(sc);
}

double	get_lt_pz(t_scene *sc, int i)
{
	return (sc->lights[i].transform.pos.z);
}

void	set_lt_pz(t_scene *sc, int i, double v)
{
	sc->lights[i].transform.pos.z = v;
	scene_mark_dirty(sc);
}
