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

/**
 * @brief Maps physics shape types to their GJK support functions.
 */
t_support_fn	get_support(t_phys_type type)
{
	if (type == TYPE_PHYS_SPHERE)
		return (gjk_support_sphere);
	if (type == TYPE_PHYS_BOX)
		return (gjk_support_box);
	if (type == TYPE_PHYS_CAPSULE)
		return (gjk_support_capsule);
	if (type == TYPE_PHYS_CYLINDER)
		return (gjk_support_cylinder);
	if (type == TYPE_PHYS_RECT)
		return (gjk_support_rect);
	if (type == TYPE_PHYS_TRI)
		return (gjk_support_tri);
	if (type == TYPE_PHYS_PYRAMID)
		return (gjk_support_pyramid);
	return (gjk_support_box);
}
