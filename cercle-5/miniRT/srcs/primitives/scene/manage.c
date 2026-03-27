/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 22:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Invalidates the scene to trigger a render update.
 * Increments the global version which forces the engine to re-bake 
 * materials and rebuild the BVH on the next frame.
 */
void	scene_invalidate(t_scene *scene)
{
	if (!scene)
		return ;
	scene->version++;
}
