/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:44:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Performs graceful cleanup of GUI and Scene resources.
 * @param scene Pointer to the scene.
 * @param gui Pointer to the GUI context.
 */
static void	cleanup_app(t_scene *scene, t_gui *gui)
{
	if (gui)
		gui_destroy(gui);
	else if (scene)
		destroy_scene(scene);
}

/**
 * @brief Loads the scene, computes the BVH, and initializes GUI data.
 * @param gui Pointer to the stack-allocated GUI structure.
 * @param scene Output pointer for the loaded scene.
 * @param path Path to the .rt scene file.
 * @param mlx Pointer to the MLX instance.
 * @return bool True on success, false on failure.
 */
static bool	init_app(t_gui *gui, t_scene **scene, const char *path, void *mlx)
{
	*scene = parse_file(path, mlx);
	if (!*scene)
	{
		ft_putstr_fd("Error: Failed to load scene: ", STDERR_FILENO);
		ft_putendl_fd((char *)path, STDERR_FILENO);
		return (false);
	}
	(*scene)->bvh = bvh_create(*scene);
	if (!(*scene)->bvh)
	{
		ft_putendl_fd("Error: Failed to create BVH", STDERR_FILENO);
		return (false);
	}
	return (gui_init(gui, *scene, mlx));
}

/**
 * @brief Starts the GUI engine and blocks until completion.
 * @param mlx Pointer to the MLX instance.
 * @param path Path to the .rt scene file.
 * @return int Exit status (0 for success, 1 for failure).
 */
int	start_app(void *mlx, const char *path)
{
	t_gui	gui;
	t_scene	*scene;

	scene = NULL;
	if (!init_app(&gui, &scene, path, mlx))
	{
		ft_putendl_fd("Error: Failed to initialize GUI", STDERR_FILENO);
		cleanup_app(scene, &gui);
		return (1);
	}
	gui.win.mlx = mlx;
	gui_loop(&gui);
	cleanup_app(scene, &gui);
	return (0);
}
