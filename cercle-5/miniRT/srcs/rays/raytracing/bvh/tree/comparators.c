/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	compare_x(const void *a, const void *b)
{
	t_build_item	*ia;
	t_build_item	*ib;

	ia = (t_build_item *)a;
	ib = (t_build_item *)b;
	if (ia->centroid.x < ib->centroid.x)
		return (-1);
	else if (ia->centroid.x > ib->centroid.x)
		return (1);
	else
		return (0);
}

int	compare_y(const void *a, const void *b)
{
	t_build_item	*ia;
	t_build_item	*ib;

	ia = (t_build_item *)a;
	ib = (t_build_item *)b;
	if (ia->centroid.y < ib->centroid.y)
		return (-1);
	else if (ia->centroid.y > ib->centroid.y)
		return (1);
	else
		return (0);
}

int	compare_z(const void *a, const void *b)
{
	t_build_item	*ia;
	t_build_item	*ib;

	ia = (t_build_item *)a;
	ib = (t_build_item *)b;
	if (ia->centroid.z < ib->centroid.z)
		return (-1);
	else if (ia->centroid.z > ib->centroid.z)
		return (1);
	else
		return (0);
}
