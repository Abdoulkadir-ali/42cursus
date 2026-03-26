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

static void	sync_compound(t_physics_body *b)
{
	if (b->is_compound)
		update_compound(b);
}

static void	integrate_part2(t_scene *scene, double dt)
{
	int	i;

	i = 0;
	while (i < scene->capsule_count)
	{
		integrate_capsule(&scene->capsules[i], dt);
		sync_compound(&scene->capsules[i++].phys);
	}
	i = 0;
	while (i < scene->tri_count)
	{
		integrate_tri(&scene->tris[i], dt);
		sync_compound(&scene->tris[i++].phys);
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		integrate_cylinder(&scene->cylinders[i], dt);
		sync_compound(&scene->cylinders[i++].phys);
	}
}

/**
 * @brief Global integration loop.
 * Updates all physical entities in the scene by one time step dt.
 * Compound bodies also re-sync their global_aabb after integration.
 */
void	integrate_bodies(t_scene *scene, double dt)
{
	int	i;

	if (!scene)
		return ;
	i = 0;
	while (i < scene->sphere_count)
	{
		integrate_sphere(&scene->spheres[i], dt);
		sync_compound(&scene->spheres[i++].phys);
	}
	i = 0;
	while (i < scene->rect_count)
	{
		integrate_rect(&scene->rects[i], dt);
		sync_compound(&scene->rects[i++].phys);
	}
	i = 0;
	while (i < scene->pyramid_count)
	{
		integrate_pyramid(&scene->pyramids[i], dt);
		sync_compound(&scene->pyramids[i++].phys);
	}
	i = 0;
	while (i < scene->box_count)
	{
		integrate_box(&scene->boxes[i], dt);
		sync_compound(&scene->boxes[i++].phys);
	}
	integrate_part2(scene, dt);
}

