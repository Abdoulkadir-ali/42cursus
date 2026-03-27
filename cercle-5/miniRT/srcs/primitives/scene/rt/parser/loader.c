/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:16:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_parse_rt(t_scene *scene, const char *path)
{
	int fd;
	bool success;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	success = parse_rt_fd(fd, scene);
	close(fd);
	return (success);
}

t_scene	*parse_file(const char *path, void *mlx)
{
	t_scene *scene;
	const char *ext;

	if (!validate_file(path))
		return (NULL);
	scene = create_scene(path);
	if (!scene)
		return (NULL);
	scene->mlx = mlx;
	ext = get_file_extension(path);
	if (ft_strcmp(ext, "rt") == 0)
	{
		if (!scene_parse_rt(scene, path))
		{
			destroy_scene(scene);
			return (NULL);
		}
	}
	else
	{
		if (!load_mesh_file(scene, path))
		{
			destroy_scene(scene);
			return (NULL);
		}
	}
	return (scene);
}
