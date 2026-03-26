/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/**
 * @brief Returns the physics body component from a hit reference.
 */
t_physics_body	*get_body_ref(t_scene *sc, t_hit_ref ref)
{
	if (ref.type == TYPE_SPHERE)
		return (&sc->spheres[ref.index].phys);
	if (ref.type == TYPE_TRI)
		return (&sc->tris[ref.index].phys);
	if (ref.type == TYPE_RECT)
		return (&sc->rects[ref.index].phys);
	if (ref.type == TYPE_PYRAMID)
		return (&sc->pyramids[ref.index].phys);
	if (ref.type == TYPE_BOX)
		return (&sc->boxes[ref.index].phys);
	if (ref.type == TYPE_CAPSULE)
		return (&sc->capsules[ref.index].phys);
	if (ref.type == TYPE_CYLINDER)
		return (&sc->cylinders[ref.index].phys);
	return (NULL);
}
