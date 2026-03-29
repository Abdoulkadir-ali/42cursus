/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:19:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:19:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_lt_bright(t_scene *sc, int i)
{
	return (sc->lights[i].brightness);
}

void	set_lt_bright(t_scene *sc, int i, double v)
{
	sc->lights[i].brightness = v;
	scene_mark_dirty(sc);
}

double	get_lt_r(t_scene *sc, int i)
{
	return (sc->lights[i].rgb.x);
}

void	set_lt_r(t_scene *sc, int i, double v)
{
	sc->lights[i].rgb.x = v;
	scene_mark_dirty(sc);
}

double	get_lt_g(t_scene *sc, int i)
{
	return (sc->lights[i].rgb.y);
}

void	set_lt_g(t_scene *sc, int i, double v)
{
	sc->lights[i].rgb.y = v;
	scene_mark_dirty(sc);
}
