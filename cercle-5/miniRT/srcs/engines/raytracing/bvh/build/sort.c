/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:07:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Comparator for sorting BVH build items along the X axis.
 */
int	compare_x(const void *a, const void *b)
{
	const t_build_item	*ia;
	const t_build_item	*ib;

	ia = (const t_build_item *)a;
	ib = (const t_build_item *)b;
	if (ia->centroid.x < ib->centroid.x)
		return (-1);
	if (ia->centroid.x > ib->centroid.x)
		return (1);
	return (0);
}

/**
 * @brief Comparator for sorting BVH build items along the Y axis.
 */
int	compare_y(const void *a, const void *b)
{
	const t_build_item	*ia;
	const t_build_item	*ib;

	ia = (const t_build_item *)a;
	ib = (const t_build_item *)b;
	if (ia->centroid.y < ib->centroid.y)
		return (-1);
	if (ia->centroid.y > ib->centroid.y)
		return (1);
	return (0);
}

/**
 * @brief Comparator for sorting BVH build items along the Z axis.
 */
int	compare_z(const void *a, const void *b)
{
	const t_build_item	*ia;
	const t_build_item	*ib;

	ia = (const t_build_item *)a;
	ib = (const t_build_item *)b;
	if (ia->centroid.z < ib->centroid.z)
		return (-1);
	if (ia->centroid.z > ib->centroid.z)
		return (1);
	return (0);
}
