/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Adds a mesh to the scene.
*/
bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	if (!DYNARRAY_ENSURE_INT(&scene->meshes, &scene->mesh_count,
			&scene->mesh_cap, sizeof(t_mesh)))
		return (false);
	if (vec3_mag_sq(mesh.transform.scale) < 1e-6)
		mesh.transform.scale = vec3(1, 1, 1);
	scene->meshes[scene->mesh_count++] = mesh;
	return (true);
}

/*
** Adds an animated mesh to the scene.
*/
bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
	if (!DYNARRAY_ENSURE_INT(&scene->animated, &scene->anim_count,
			&scene->anim_cap, sizeof(t_skinned_mesh)))
		return (false);
	scene->animated[scene->anim_count++] = animated;
	return (true);
}

/*
** Appends a pre-built group to the scene.
*/
bool	scene_add_group(t_scene *scene, t_mesh_group g)
{
	if (!DYNARRAY_ENSURE_INT(&scene->groups, &scene->group_count,
			&scene->group_cap, sizeof(t_mesh_group)))
		return (false);
	scene->groups[scene->group_count++] = g;
	return (true);
}

/*
** Builds a t_mesh_group from the submeshes in scene->meshes[start_mesh .. mesh_count-1]
** (which must already be baked via mesh_apply_transform so their bboxes are valid),
** then appends it to scene->groups[].
** Returns false only on allocation failure — the scene is unaffected on failure.
*/
bool	scene_add_group_for_subs(t_scene *scene, const char *path, int start_mesh)
{
	t_mesh_group	g;
	t_aabb			bbox;
	const char		*slash;
	char			*dot;
	int				si;

	if (scene->mesh_count <= start_mesh)
		return (false);
	ft_memset(&g, 0, sizeof(g));
	g.path = ft_strdup(path ? path : "");
	slash = path ? ft_strrchr(path, '/') : NULL;
	g.name = ft_strdup(slash ? slash + 1 : (path ? path : ""));
	if (!g.name || !g.path)
	{
		free(g.name);
		free(g.path);
		return (false);
	}
	dot = ft_strrchr(g.name, '.');
	if (dot)
		*dot = '\0';
	g.start = start_mesh;
	g.sub_count = scene->mesh_count - start_mesh;
	g.anim_base = scene->meshes[start_mesh].anim_base;
	g.anim_clip_count = scene->meshes[start_mesh].anim_clip_count;
	/* Compute pivot = centre of union bbox of all baked submeshes */
	bbox = scene->meshes[start_mesh].bbox;
	si = start_mesh + 1;
	while (si < scene->mesh_count)
		bbox = aabb_union(&bbox, &scene->meshes[si++].bbox);
	g.pivot = vec3(
		(bbox.min.x + bbox.max.x) * 0.5,
		(bbox.min.y + bbox.max.y) * 0.5,
		(bbox.min.z + bbox.max.z) * 0.5);
	g.phys = scene->meshes[start_mesh].phys;
	g.collider = scene->meshes[start_mesh].collider;
	g.transform.scale = vec3(1, 1, 1);
	return (scene_add_group(scene, g));
}
