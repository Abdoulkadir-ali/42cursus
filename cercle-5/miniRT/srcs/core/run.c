/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Root dispatcher for the miniRT application run cycle.
 * @param path The scene file to execute.
 * @return int Exit code.
 */
int	run_app(const char *path)
{
	t_scene	*scene;
	t_gui	*gui;
	void	*mlx;

	ft_print_debug("DEBUG: Initializing MLX for: %s\n", path);
	mlx = mlx_init();
	if (!mlx)
	{
		ft_putendl_fd("Error: Failed to initialize MLX", STDERR_FILENO);
		return (1);
	}
	scene = NULL;
	gui = init_app(path, &scene, mlx);
	return (start_app(gui, scene, mlx));
}
