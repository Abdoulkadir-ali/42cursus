/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_ambient_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:20:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_amb_b(t_scene *sc, int i)
{
	(void)i;
	return (sc->ambient.rgb.z);
}

void	set_amb_b(t_scene *sc, int i, double v)
{
	(void)i;
	sc->ambient.rgb.z = v;
	scene_mark_dirty(sc);
}
