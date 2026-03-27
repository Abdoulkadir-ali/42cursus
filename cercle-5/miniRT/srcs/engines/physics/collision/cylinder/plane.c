/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	cyl_plane_contacts(t_scene *s, t_cylinder *cy, t_gjk_shape *sa,
		t_contact *c, int count, int max)
{
	(void)cy;
	return (gjk_vs_all_planes(sa, &cy->phys, &cy->transform, s, c, count, max));
}
