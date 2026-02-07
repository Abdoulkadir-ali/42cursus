/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 02:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/fbx.h"
#include "scene.h"
#include "libft.h"
#include <stdlib.h>

bool	parse_fbx(const char *path, t_scene *scene)
{
	t_skinned_mesh  mesh;

	// 1. Initialize empty
	ft_memset(&mesh, 0, sizeof(t_skinned_mesh));
	
	// 2. Parse the file stub
	mesh.base.name = ft_strdup(path);
	// ... FBX parsing logic would go here ...
	
	// 3. Inject directly into scene
	if (!scene_add_animated(scene, mesh))
	{
		free(mesh.base.name);
		return (false);
	}
	
	return (true);
}
