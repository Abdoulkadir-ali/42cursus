/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_lights_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_lt_b(t_scene *sc, int i)
{
	return (sc->lights[i].rgb.z);
}

void	set_lt_b(t_scene *sc, int i, double v)
{
	sc->lights[i].rgb.z = v;
	scene_mark_dirty(sc);
}

double	get_lt_px(t_scene *sc, int i)
{
	return (sc->lights[i].transform.pos.x);
}

void	set_lt_px(t_scene *sc, int i, double v)
{
	sc->lights[i].transform.pos.x = v;
	scene_mark_dirty(sc);
}
