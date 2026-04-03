/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:58:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	reset_meshes(t_scene *sc, t_scene_snap *snap)
{
	size_t	i;

	i = 0;
	while (i < snap->mesh_count && i < sc->mesh_count)
	{
		sc->meshes[i].transform = snap->meshes[i].transform;
		sc->meshes[i].mat_id = snap->meshes[i].mat_id;
		sc->meshes[i].phys = snap->meshes[i].phys;
		i++;
	}
	while (i < sc->mesh_count)
		mesh_free(&sc->meshes[i++]);
	sc->mesh_count = snap->mesh_count;
	sc->mesh_group_count = snap->mesh_group_count;
}

void	reset_groups(t_scene *sc, t_scene_snap *snap)
{
	size_t	i;

	i = 0;
	while (i < snap->group_count && i < sc->group_count)
	{
		sc->groups[i].transform = snap->groups[i].transform;
		sc->groups[i].pivot = snap->groups[i].pivot;
		sc->groups[i].phys = snap->groups[i].phys;
		i++;
	}
	while (i < sc->group_count)
	{
		free(sc->groups[i].name);
		free(sc->groups[i].path);
		i++;
	}
	sc->group_count = snap->group_count;
}

void	reset_primitives(t_scene *sc, t_scene_snap *snap)
{
	sc->sphere_count = snap->sphere_count;
	ft_memcpy(sc->spheres, snap->spheres,
		snap->sphere_count * sizeof(t_sphere));
	sc->plane_count = snap->plane_count;
	ft_memcpy(sc->planes, snap->planes,
		snap->plane_count * sizeof(t_plane));
	sc->cylinder_count = snap->cylinder_count;
	ft_memcpy(sc->cylinders, snap->cylinders,
		snap->cylinder_count * sizeof(t_cylinder));
	sc->cone_count = snap->cone_count;
	ft_memcpy(sc->cones, snap->cones, snap->cone_count * sizeof(t_cone));
	sc->light_count = snap->light_count;
	ft_memcpy(sc->lights, snap->lights,
		snap->light_count * sizeof(t_light));
	sc->mat_count = snap->mat_count;
	ft_memcpy(sc->materials, snap->materials,
		snap->mat_count * sizeof(t_material));
}

void	reset_extra(t_scene *sc, t_scene_snap *snap)
{
	if (snap->box_count)
		ft_memcpy(sc->boxes, snap->boxes,
			snap->box_count * sizeof(t_box));
	sc->box_count = snap->box_count;
	if (snap->capsule_count)
		ft_memcpy(sc->capsules, snap->capsules,
			snap->capsule_count * sizeof(t_capsule));
	sc->capsule_count = snap->capsule_count;
	if (snap->rect_count)
		ft_memcpy(sc->rects, snap->rects,
			snap->rect_count * sizeof(t_rect));
	sc->rect_count = snap->rect_count;
	if (snap->pyramid_count)
		ft_memcpy(sc->pyramids, snap->pyramids,
			snap->pyramid_count * sizeof(t_pyramid));
	sc->pyramid_count = snap->pyramid_count;
	if (snap->tri_count)
		ft_memcpy(sc->tris, snap->tris,
			snap->tri_count * sizeof(t_tri_shape));
	sc->tri_count = snap->tri_count;
}
