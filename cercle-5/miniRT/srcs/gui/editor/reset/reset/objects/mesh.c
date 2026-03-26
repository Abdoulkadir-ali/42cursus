/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	reset_mesh(t_scene *sc, t_scene_snap *s)
{
	int	i;

	i = -1;
	while (++i < s->mesh_count && i < sc->mesh_count)
	{
		sc->meshes[i].transform = s->meshes[i].transform;
		sc->meshes[i].mat_id = s->meshes[i].mat_id;
		sc->meshes[i].phys = s->meshes[i].phys;
	}
	while (i < sc->mesh_count)
		mesh_free(&sc->meshes[i++]);
	sc->mesh_count = s->mesh_count;
	sc->mesh_group_count = s->mesh_group_count;
	i = -1;
	while (++i < s->group_count && i < sc->group_count)
	{
		sc->groups[i].transform = s->groups[i].transform;
		sc->groups[i].pivot = s->groups[i].pivot;
		sc->groups[i].phys = s->groups[i].phys;
	}
	while (i < sc->group_count)
	{
		free(sc->groups[i].name);
		free(sc->groups[i++].path);
	}
	sc->group_count = s->group_count;
}
