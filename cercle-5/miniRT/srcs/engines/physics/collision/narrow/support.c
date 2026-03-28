/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_support_fn	get_support(t_phys_type type)
{
	static t_support_fn	table[TYPE_PHYS_MAX] = {
	[TYPE_PHYS_SPHERE] = gjk_support_sphere,
	[TYPE_PHYS_BOX] = gjk_support_box,
	[TYPE_PHYS_CAPSULE] = gjk_support_capsule,
	[TYPE_PHYS_CYLINDER] = gjk_support_cylinder,
	[TYPE_PHYS_RECT] = gjk_support_rect,
	[TYPE_PHYS_TRI] = gjk_support_tri,
	[TYPE_PHYS_PYRAMID] = gjk_support_pyramid,
	[TYPE_PHYS_MESH] = gjk_support_mesh
	};

	if (type < 0 || type >= TYPE_PHYS_MAX)
		return (gjk_support_box);
	return (table[type]);
}
