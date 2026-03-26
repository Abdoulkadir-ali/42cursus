/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "gui.h"

/**
 * @brief Starts the GUI engine and blocks until completion.
 * @param gui Pointer to the initialized GUI.
 * @param scene Pointer to the scene.
 * @param mlx Pointer to the MLX instance.
 * @return int Exit status (0 for success, 1 for failure).
 */
int	start_app(t_gui *gui, t_scene *scene, void *mlx)
{
	if (!gui)
	{
		ft_putendl_fd("Error: Failed to initialize GUI", STDERR_FILENO);
		core_cleanup(scene, NULL);
		return (1);
	}
	gui->win.mlx = mlx;
	gui_loop(gui);
	core_cleanup(scene, gui);
	return (0);
}
