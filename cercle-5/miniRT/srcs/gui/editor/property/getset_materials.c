/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:03:29 by abdoali          ###   ########.fr       */
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

double	get_mat_emit_r(t_scene *sc, int i)
{
	return (sc->materials[i].emission.x);
}

void	set_mat_emit_r(t_scene *sc, int i, double v)
{
	sc->materials[i].emission.x = v;
	scene_mark_dirty(sc);
}

double	get_mat_emit_g(t_scene *sc, int i)
{
	return (sc->materials[i].emission.y);
}

void	set_mat_emit_g(t_scene *sc, int i, double v)
{
	sc->materials[i].emission.y = v;
	scene_mark_dirty(sc);
}

double	get_mat_emit_b(t_scene *sc, int i)
{
	return (sc->materials[i].emission.z);
}

void	set_mat_emit_b(t_scene *sc, int i, double v)
{
	sc->materials[i].emission.z = v;
	scene_mark_dirty(sc);
}
