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

/**
 * Pure Factory orchestrator for mesh resource retrieval.
 * This function resolves how to build a t_mesh_resource from a file
 * without knowledge of the global scene state.
 */
bool	mesh_build_resource(const char *path, const char *ext,
			t_mesh_resource *out)
{
	if (!validate_file(path))
	{
		fprintf(stderr, "Error: File not found or invalid: %s\n", path);
		return (false);
	}
	ft_memset(out, 0, sizeof(*out));
	if (ext && ft_strcmp(ext, ".fbx") == 0)
		return (build_fbx_resource(path, out));
	if (ext && ft_strcmp(ext, ".obj") == 0)
		return (build_obj_resource(path, out));
	if (ext && ft_strcmp(ext, ".fdf") == 0)
		return (build_fdf_resource(path, out));
	if (ext && ft_strcmp(ext, ".glb") == 0)
		return (build_glb_resource(path, out));
	return (false);
}
