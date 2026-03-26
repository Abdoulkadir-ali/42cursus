/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "objects.h"
#include "scene.h"

static void	integrate_part2(t_scene *scene, double dt)
{
	int	i;

	i = 0;
	while (i < scene->capsule_count)
		integrate_capsule(&scene->capsules[i++], dt);
	i = 0;
	while (i < scene->tri_count)
		integrate_tri(&scene->tris[i++], dt);
	i = 0;
	while (i < scene->cylinder_count)
		integrate_cylinder(&scene->cylinders[i++], dt);
}

/**
 * @brief Global integration loop. 
 * Updates all physical entities in the scene by one time step dt.
 */
void	integrate_bodies(t_scene *scene, double dt)
{
	int	i;

	if (!scene)
		return ;
	i = 0;
	while (i < scene->sphere_count)
		integrate_sphere(&scene->spheres[i++], dt);
	i = 0;
	while (i < scene->rect_count)
		integrate_rect(&scene->rects[i++], dt);
	i = 0;
	while (i < scene->pyramid_count)
		integrate_pyramid(&scene->pyramids[i++], dt);
	i = 0;
	while (i < scene->box_count)
		integrate_box(&scene->boxes[i++], dt);
	integrate_part2(scene, dt);
}
