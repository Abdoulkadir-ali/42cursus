/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 02:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "objects/rt.h"
#include "objects/fbx.h"
#include "objects/obj.h"
#include "objects/fdf.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const char	*get_extension(const char *path)
{
	const char	*dot;

	dot = strrchr(path, '.');
	if (!dot || dot == path)
		return ("");
	return (dot + 1);
}

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
	else
		printf("Error: Unsupported file format: %s\n", ext);
	
	if (!success)
	{
		destroy_scene(scene);
		return (NULL);
	}
	return (scene);
}
