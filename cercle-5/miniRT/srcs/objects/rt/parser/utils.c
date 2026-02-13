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

static bool	parse_by_ext(const char *ext, const char *path, t_scene *scene)
{
	if (ft_strcmp(ext, "rt") == 0)
		return (parse_rt(path, scene));
	if (ft_strcmp(ext, "fbx") == 0)
		return (parse_fbx(path, scene));
	if (ft_strcmp(ext, "obj") == 0)
		return (parse_obj(path, scene));
	if (ft_strcmp(ext, "fdf") == 0)
		return (parse_fdf(path, scene));
	if (ft_strcmp(ext, "glb") == 0)
		return (parse_glb(path, scene));
	printf("Error: Unsupported file extension: .%s\n", ext);
	return (false);
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
