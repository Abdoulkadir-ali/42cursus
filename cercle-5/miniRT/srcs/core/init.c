/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "scene.h"
#include "raytracing.h"
#include "gui.h"

/**
 * @brief Loads the scene, computes the BVH, and initializes GUI data.
 * @param path Path to the .rt scene file.
 * @param scene Output pointer for the loaded scene.
 * @param mlx Pointer to the MLX instance.
 * @return t_gui* Pointer to the initialized GUI, or NULL on failure.
 */
t_gui	*init_app(const char *path, t_scene **scene, void *mlx)
{
	t_gui	*gui;

	*scene = parse_file(path, mlx);
	if (!*scene)
	{
		ft_putstr_fd("Error: Failed to load scene: ", STDERR_FILENO);
		ft_putendl_fd((char *)path, STDERR_FILENO);
		return (NULL);
	}
	(*scene)->bvh = bvh_create(*scene);
	if (!(*scene)->bvh)
	{
		ft_putendl_fd("Error: Failed to create BVH", STDERR_FILENO);
		return (NULL);
	}
	gui = gui_init(*scene, mlx);
	return (gui);
}
