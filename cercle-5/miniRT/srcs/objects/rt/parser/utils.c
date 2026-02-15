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

#include "objects.h"
#include "scene.h"

static bool	is_mesh_ext(const char *ext)
{
	return (ft_strcmp(ext, "fbx") == 0 || ft_strcmp(ext, "obj") == 0
		|| ft_strcmp(ext, "fdf") == 0 || ft_strcmp(ext, "glb") == 0);
}

static void	setup_default_scene(t_scene *scene)
{
	t_plane	plane;
	t_light	light;

	scene->ambient.brightness = 0.3;
	scene->ambient.rgb = vec3(255, 255, 255);
	scene->camera.fov = 70;
	ft_memset(&light, 0, sizeof(t_light));
	light.type = LIGHT_POINT;
	light.transform.pos = vec3(15, 25, 30);
	light.brightness = 0.8;
	light.rgb = vec3(255, 255, 255);
	scene_add_light(scene, light);
	light.transform.pos = vec3(-15, 40, 10);
	scene_add_light(scene, light);
	light.transform.pos = vec3(0, 60, -20);
	scene_add_light(scene, light);
	ft_memset(&plane, 0, sizeof(t_plane));
	plane.transform.pos = vec3(0, 0, 0);
	plane.transform.forward = vec3(0, 1, 0);
	plane.temp_color = vec3(150, 150, 150);
	scene_add_plane(scene, plane);
}

static void	autoframe_camera(t_scene *scene)
{
	t_mesh	*mesh;
	t_vec3	center;
	double	size;
	t_vec3	fwd;

	if (scene->mesh_count <= 0)
		return ;
	mesh = &scene->meshes[scene->mesh_count - 1];
	center = vec3_scale(vec3_add(mesh->bbox.min, mesh->bbox.max), 0.5);
	size = vec3_mag(vec3_sub(mesh->bbox.max, mesh->bbox.min));
	if (size < 1e-6)
		size = 10.0;
	scene->camera.transform.pos = vec3_add(center, vec3(0, size * 0.3, size
				* 1.2));
	fwd = vec3_norm(vec3_sub(center, scene->camera.transform.pos));
	scene->camera.transform.forward = fwd;
	scene->camera.transform.rotation.pitch = asin(fwd.y);
	scene->camera.transform.rotation.yaw = atan2(fwd.x, fwd.z);
	if (scene->light_count > 0)
		scene->lights[0].transform.pos = vec3_add(center, vec3(size * 0.5, size
					* 1.0, size * 0.8));
}

static bool	parse_by_ext(const char *ext, const char *path, t_scene *scene)
{
	bool	ok;

	if (is_mesh_ext(ext))
		setup_default_scene(scene);
	if (ft_strcmp(ext, "rt") == 0)
		return (parse_rt(path, scene));
	if (ft_strcmp(ext, "fbx") == 0)
		ok = parse_fbx(path, scene);
	else if (ft_strcmp(ext, "obj") == 0)
		ok = parse_obj(path, scene);
	else if (ft_strcmp(ext, "fdf") == 0)
		ok = parse_fdf(path, scene);
	else if (ft_strcmp(ext, "glb") == 0)
		ok = parse_glb(path, scene);
	else
	{
		printf("Error: Unsupported file extension: .%s\n", ext);
		return (false);
	}
	if (ok)
		autoframe_camera(scene);
	return (ok);
}

static t_scene	*init_scene(const char *path, void *mlx)
{
	t_scene	*scene;

	scene = create_scene(path);
	if (!scene)
	{
		printf("Error: Failed to create scene object for %s\n", path);
		return (NULL);
	}
	scene->mlx = mlx;
	return (scene);
}

t_scene	*parse_file(const char *path, void *mlx)
{
	t_scene		*scene;
	const char	*ext;
	bool		success;

	ext = rt_get_extension(path);
	if (!validate_file(path))
	{
		printf("Error: File not found or invalid: %s\n", path);
		return (NULL);
	}
	scene = init_scene(path, mlx);
	if (!scene)
		return (NULL);
	success = parse_by_ext(ext, path, scene);
	if (!success)
	{
		printf("Error: Failed to parse %s\n", path);
		destroy_scene(scene);
		return (NULL);
	}
	return (scene);
}
