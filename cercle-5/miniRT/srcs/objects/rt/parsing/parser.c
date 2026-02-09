/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Extracts the file extension from a path.
 * 
 * @param path The file path.
 * @return The extension string (without the dot).
 */
static const char	*get_extension(const char *path)
{
	const char	*dot;

	dot = ft_strrchr(path, '.');
	if (!dot || dot == path)
		return ("");
	return (dot + 1);
}

/**
 * Highly level entry point for parsing any supported scene file.
 * 
 * @param path The file path.
 * @return The allocated and parsed scene, or NULL on failure.
 */
t_scene	*parse_file(const char *path)
{
	t_scene		*scene;
	const char	*ext;
	bool		success;

	scene = create_scene(path);
	if (!scene)
		return (NULL);
	ext = get_extension(path);
	success = false;
	if (ft_strcmp(ext, "rt") == 0)
		success = parse_rt(path, scene);
	else if (ft_strcmp(ext, "fbx") == 0)
		success = parse_fbx(path, scene);
	else if (ft_strcmp(ext, "obj") == 0)
		success = parse_obj(path, scene);
	else if (ft_strcmp(ext, "fdf") == 0)
		success = parse_fdf(path, scene);
	else if (ft_strcmp(ext, "glb") == 0)
		success = parse_glb(path, scene);
	if (!success)
	{
		destroy_scene(scene);
		return (NULL);
	}
	return (scene);
}
