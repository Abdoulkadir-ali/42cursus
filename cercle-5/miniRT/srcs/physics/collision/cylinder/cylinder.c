/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:08:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_cylinder(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_cylinder	*cy = &s->cylinders[idx];
	t_aabb		ca;
	t_gjk_shape	sa;

	if (cy->phys.is_static) return (count);
	ca = cylinder_aabb(cy);
	sa = (t_gjk_shape){cy, gjk_support_cylinder, cy->phys.center};
	count = cyl_plane_contacts(s, cy, &sa, c, count, max);
	return (cyl_vs_others(s, idx, cy, ca, c, count, max));
}
