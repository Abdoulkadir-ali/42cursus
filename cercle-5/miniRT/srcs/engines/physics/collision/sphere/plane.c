/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:33:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "physics.h"
#include "scene.h"

/**
 * @brief Dispatcher for analytical sphere-plane collision.
 * Standardizes the static query interface for symmetry.
 */
int	sphere_plane_contacts(t_scene *s, t_sphere *sp, t_gjk_shape *sa,
		t_contact *c, int count, int max)
{
	(void)sp;
	return (gjk_vs_all_planes(sa, &sp->phys, &sp->transform, s, c, count, max));
}
