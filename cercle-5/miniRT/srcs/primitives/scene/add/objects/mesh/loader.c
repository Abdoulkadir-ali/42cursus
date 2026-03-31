/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:48:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:53:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

#include "scene.h"

/**
 * High-level orchestrator for mesh file integration.
 * Resolves the appropriate format loader based on file extension
 * and orchestrates the injection of assets into the global scene.
 */
bool	scene_add_mesh_file(t_scene *scene, const char *path)
{
	const char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext)
		return (false);
	if (ft_strcmp(ext, ".fbx") == 0)
		return (parse_fbx(path, scene));
	if (ft_strcmp(ext, ".obj") == 0)
		return (parse_obj(path, scene));
	if (ft_strcmp(ext, ".fdf") == 0)
		return (parse_fdf(path, scene));
	if (ft_strcmp(ext, ".glb") == 0)
		return (parse_glb(path, scene));
	return (false);
}
