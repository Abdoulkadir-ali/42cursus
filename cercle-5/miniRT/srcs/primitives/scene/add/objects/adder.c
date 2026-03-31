/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 21:56:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
	if (!DYNARRAY_ENSURE_INT(&scene->animated, &scene->anim_count,
			&scene->anim_cap, sizeof(t_skinned_mesh)))
		return (false);
	scene->animated[scene->anim_count++] = animated;
	return (true);
}

static bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	if (!DYNARRAY_ENSURE_INT(&scene->meshes, &scene->mesh_count,
			&scene->mesh_cap, sizeof(t_mesh)))
		return (false);
	if (vec3_mag_sq(mesh.transform.scale) < 1e-6)
		mesh.transform.scale = vec3(1, 1, 1);
	scene->meshes[scene->mesh_count++] = mesh;
	return (true);
}

static bool	scene_add_group(t_scene *scene, t_mesh_group g)
{
	if (!DYNARRAY_ENSURE_INT(&scene->groups, &scene->group_count,
			&scene->group_cap, sizeof(t_mesh_group)))
		return (false);
	scene->groups[scene->group_count++] = g;
	return (true);
}

bool	scene_add_objects(t_scene *scene, const char *path)
{
	t_mesh_resource	res;
	const char		*ext;
	int				start;
	int				i;

	if (!scene || !path)
		return (false);
	ext = ft_strrchr(path, '.');
	if (!ext)
		return (false);
	if (!mesh_build_resource(path, ext, &res))
		return (false);
	start = scene->mesh_count;
	i = -1;
	while (++i < res.mesh_count)
	{
		if (!scene_add_mesh(scene, res.meshes[i]))
			return (false);
	}
	i = -1;
	while (++i < res.group_count)
	{
		if (!scene_add_group(scene, res.groups[i]))
			return (false);
	}
	if (scene->mesh_count > start)
		scene_add_group_for_subs(scene, path, start);
	return (true);
}

