/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 02:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/fdf.h"
#include "scene.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

bool	parse_fdf(const char *path, t_scene *scene)
{
	t_mesh  mesh;

	printf("FDF Parser: Attempting to load heightmap from %s\n", path);
	
	// 1. Initialize empty
	ft_memset(&mesh, 0, sizeof(t_mesh));
	mesh.name = ft_strdup(path);
	
	// 2. Inject directly into scene
	if (!scene_add_mesh(scene, mesh))
	{
		free(mesh.name);
		return (false);
	}
	printf("FDF Parser: Successfully injected placeholder mesh for %s\n", path);
	return (true);
}
