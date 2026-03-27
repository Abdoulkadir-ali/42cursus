/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:58:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Dispatcher for complex mesh assets (GLB, FBX, FDF, OBJ).
 */
bool	dispatch_meshes(t_scene *scene, t_parser *p, char *id)
{
	if (ft_strcmp(id, "glb") == 0)
		return (parse_glb_entry(scene, p));
	if (ft_strcmp(id, "fbx") == 0)
		return (parse_fbx_entry(scene, p));
	if (ft_strcmp(id, "fdf") == 0)
		return (parse_fdf_entry(scene, p));
	if (ft_strcmp(id, "obj") == 0)
		return (parse_obj_entry(scene, p));
	return (false);
}
