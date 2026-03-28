/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:01:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	capsule_plane_contacts(t_physics *phys, int idx, t_gjk_shape *sa,
		t_contact *c, int count, int max)
{
	return (gjk_vs_all_planes(sa, idx, phys, c, count, max));
}
