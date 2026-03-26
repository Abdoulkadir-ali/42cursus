/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	loop_meshes(t_scene_snap *s, t_scene *sc)
{
	int	i;

	i = -1;
	while (s->meshes && ++i < sc->mesh_count)
	{
		s->meshes[i].transform = sc->meshes[i].transform;
		s->meshes[i].mat_id = sc->meshes[i].mat_id;
		s->meshes[i].phys = sc->meshes[i].phys;
		s->meshes[i].current_anim = sc->meshes[i].current_anim;
		s->meshes[i].anim_time = sc->meshes[i].anim_time;
	}
}

static void	loop_groups(t_scene_snap *s, t_scene *sc)
{
	int	i;

	i = -1;
	while (s->groups && ++i < sc->group_count)
	{
		s->groups[i].transform = sc->groups[i].transform;
		s->groups[i].pivot = sc->groups[i].pivot;
		s->groups[i].phys = sc->groups[i].phys;
	}
}

void	snap_mesh(t_scene_snap *s, t_scene *sc)
{
	s->mesh_count = sc->mesh_count;
	s->meshes = malloc(sc->mesh_count * sizeof(t_mesh_snap));
	loop_meshes(s, sc);
	s->group_count = sc->group_count;
	s->groups = malloc(sc->group_count * sizeof(t_group_snap));
	loop_groups(s, sc);
	s->mesh_group_count = sc->mesh_group_count;
}
