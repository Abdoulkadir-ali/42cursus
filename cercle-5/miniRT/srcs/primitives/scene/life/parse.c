/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "raytracing.h"

static bool	is_rt_ext(const char *ext)
{
	return (ext && ft_strcmp(ext, "rt") == 0);
}

bool	load_scene(t_scene *scene, const char *path)
{
	const char	*ext;
	size_t		start;

	if (!scene || !path)
		return (false);
	ext = rt_get_extension(path);
	if (!validate_file(path))
	{
		fprintf(stderr, "Error: File not found: %s\n", path);
		return (false);
	}
	if (is_rt_ext(ext))
		return (parse_rt_worker(path, scene));
	setup_default_scene(scene);
	start = scene->mesh_count;
	if (!scene_add_objects(scene, path))
		return (false);
	align_and_frame_meshes(scene, start);
	return (true);
}

t_scene	*parse_file(const char *path, void *mlx)
{
	t_scene	*scene;

	scene = create_scene(path);
	if (!scene)
		return (NULL);
	scene->mlx = mlx;
	if (!load_scene(scene, path))
	{
		destroy_scene(scene);
		return (NULL);
	}
	ft_print_debug("PARSE: building scene BVH...\n");
	scene->bvh = bvh_create(scene);
	if (!scene->bvh)
	{
		destroy_scene(scene);
		return (NULL);
	}
	ft_print_debug("PARSE: scene BVH done, startup complete\n");
	return (scene);
}
