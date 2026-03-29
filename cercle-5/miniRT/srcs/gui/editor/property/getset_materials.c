/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:20:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_mat_rough(t_scene *sc, int i)
{
	return (sc->materials[i].roughness);
}

void	set_mat_rough(t_scene *sc, int i, double v)
{
	sc->materials[i].roughness = v;
	scene_mark_dirty(sc);
}

double	get_mat_metal(t_scene *sc, int i)
{
	return (sc->materials[i].metallic);
}

void	set_mat_metal(t_scene *sc, int i, double v)
{
	sc->materials[i].metallic = v;
	scene_mark_dirty(sc);
}

double	get_mat_opac(t_scene *sc, int i)
{
	return (sc->materials[i].transparency);
}

void	set_mat_opac(t_scene *sc, int i, double v)
{
	sc->materials[i].transparency = v;
	scene_mark_dirty(sc);
}
