/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Checks for AABB intersection in local sub-shape space.
 */
bool	aabb_overlap_local(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}
