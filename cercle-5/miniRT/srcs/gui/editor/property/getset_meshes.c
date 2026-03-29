/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_meshes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:20:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:20:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_mesh_px(t_scene *sc, int i)
{
	return (sc->meshes[i].transform.pos.x);
}

void	set_mesh_px(t_scene *sc, int i, double v)
{
	sc->meshes[i].transform.pos.x = v;
	scene_mark_dirty(sc);
}

double	get_mesh_py(t_scene *sc, int i)
{
	return (sc->meshes[i].transform.pos.y);
}

void	set_mesh_py(t_scene *sc, int i, double v)
{
	sc->meshes[i].transform.pos.y = v;
	scene_mark_dirty(sc);
}

double	get_mesh_pz(t_scene *sc, int i)
{
	return (sc->meshes[i].transform.pos.z);
}

void	set_mesh_pz(t_scene *sc, int i, double v)
{
	sc->meshes[i].transform.pos.z = v;
	scene_mark_dirty(sc);
}
