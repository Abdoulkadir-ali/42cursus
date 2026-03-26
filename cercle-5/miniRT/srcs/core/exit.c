/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "gui.h"
#include "scene.h"

/**
 * @brief Performs graceful cleanup of GUI and Scene resources.
 * @param scene Pointer to the scene.
 * @param gui Pointer to the GUI context.
 */
void	core_cleanup(t_scene *scene, t_gui *gui)
{
	if (gui)
		gui_destroy(gui);
	else if (scene)
		destroy_scene(scene);
}
