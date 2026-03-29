/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_meshes_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:21:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:21:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "property.h"

double	get_mesh_sx(t_scene *sc, int i)
{
	return (sc->meshes[i].transform.scale.x);
}

void	set_mesh_sx(t_scene *sc, int i, double v)
{
	sc->meshes[i].transform.scale.x = v;
	scene_mark_dirty(sc);
}

double	get_mesh_sy(t_scene *sc, int i)
{
	return (sc->meshes[i].transform.scale.y);
}

void	set_mesh_sy(t_scene *sc, int i, double v)
{
	sc->meshes[i].transform.scale.y = v;
	scene_mark_dirty(sc);
}

double	get_mesh_sz(t_scene *sc, int i)
{
	return (sc->meshes[i].transform.scale.z);
}

void	set_mesh_sz(t_scene *sc, int i, double v)
{
	sc->meshes[i].transform.scale.z = v;
	scene_mark_dirty(sc);
}
