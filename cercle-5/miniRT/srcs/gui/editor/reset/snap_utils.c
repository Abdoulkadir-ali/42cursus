/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:58:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	snap_array(void **dst, void *src, size_t count, size_t sz)
{
	*dst = NULL;
	if (!count)
		return ;
	*dst = malloc(count * sz);
	if (*dst)
		ft_memcpy(*dst, src, count * sz);
}

void	snap_meshes(t_scene_snap *snap, t_scene *sc)
{
	size_t	i;

	snap->mesh_count = sc->mesh_count;
	snap->meshes = NULL;
	if (!sc->mesh_count)
		return ;
	snap->meshes = malloc(sc->mesh_count * sizeof(t_mesh_snap));
	if (!snap->meshes)
		return ;
	i = 0;
	while (i < sc->mesh_count)
	{
		snap->meshes[i].transform = sc->meshes[i].transform;
		snap->meshes[i].mat_id = sc->meshes[i].mat_id;
		snap->meshes[i].phys = sc->meshes[i].phys;
		i++;
	}
}

void	snap_groups(t_scene_snap *snap, t_scene *sc)
{
	size_t	i;

	snap->group_count = sc->group_count;
	snap->groups = NULL;
	if (!sc->group_count)
		return ;
	snap->groups = malloc(sc->group_count * sizeof(t_group_snap));
	if (!snap->groups)
		return ;
	i = 0;
	while (i < sc->group_count)
	{
		snap->groups[i].transform = sc->groups[i].transform;
		snap->groups[i].pivot = sc->groups[i].pivot;
		snap->groups[i].phys = sc->groups[i].phys;
		i++;
	}
}

void	snap_primitives(t_scene_snap *snap, t_scene *sc)
{
	snap_array((void **)&snap->spheres, sc->spheres,
		sc->sphere_count, sizeof(t_sphere));
	snap->sphere_count = sc->sphere_count;
	snap_array((void **)&snap->planes, sc->planes,
		sc->plane_count, sizeof(t_plane));
	snap->plane_count = sc->plane_count;
	snap_array((void **)&snap->cylinders, sc->cylinders,
		sc->cylinder_count, sizeof(t_cylinder));
	snap->cylinder_count = sc->cylinder_count;
	snap_array((void **)&snap->cones, sc->cones,
		sc->cone_count, sizeof(t_cone));
	snap->cone_count = sc->cone_count;
	snap_array((void **)&snap->lights, sc->lights,
		sc->light_count, sizeof(t_light));
	snap->light_count = sc->light_count;
	snap_array((void **)&snap->materials, sc->materials,
		sc->mat_count, sizeof(t_material));
	snap->mat_count = sc->mat_count;
}

void	snap_extra(t_scene_snap *snap, t_scene *sc)
{
	snap_array((void **)&snap->boxes, sc->boxes,
		sc->box_count, sizeof(t_box));
	snap->box_count = sc->box_count;
	snap_array((void **)&snap->capsules, sc->capsules,
		sc->capsule_count, sizeof(t_capsule));
	snap->capsule_count = sc->capsule_count;
	snap_array((void **)&snap->rects, sc->rects,
		sc->rect_count, sizeof(t_rect));
	snap->rect_count = sc->rect_count;
	snap_array((void **)&snap->pyramids, sc->pyramids,
		sc->pyramid_count, sizeof(t_pyramid));
	snap->pyramid_count = sc->pyramid_count;
	snap_array((void **)&snap->tris, sc->tris,
		sc->tri_count, sizeof(t_tri_shape));
	snap->tri_count = sc->tri_count;
}
