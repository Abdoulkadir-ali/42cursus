/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:20:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_amb_bright(t_scene *sc, int i)
{
	(void)i;
	return (sc->ambient.brightness);
}

void	set_amb_bright(t_scene *sc, int i, double v)
{
	(void)i;
	sc->ambient.brightness = v;
	scene_mark_dirty(sc);
}

double	get_amb_r(t_scene *sc, int i)
{
	(void)i;
	return (sc->ambient.rgb.x);
}

void	set_amb_r(t_scene *sc, int i, double v)
{
	(void)i;
	sc->ambient.rgb.x = v;
	scene_mark_dirty(sc);
}

double	get_amb_g(t_scene *sc, int i)
{
	(void)i;
	return (sc->ambient.rgb.y);
}

void	set_amb_g(t_scene *sc, int i, double v)
{
	(void)i;
	sc->ambient.rgb.y = v;
	scene_mark_dirty(sc);
}
