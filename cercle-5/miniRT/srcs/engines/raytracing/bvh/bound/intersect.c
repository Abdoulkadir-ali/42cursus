/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Fast AABB intersection test using the branchless slabs method.
 * Uses __builtin_fmin/__builtin_fmax which often map to direct CPU instructions.
 * Handles the tnear > tfar case and clips tnear to 0.0 for rays inside.
 */
bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
		double *tmax)
{
	double	t1;
	double	t2;
	double	tnear;
	double	tfar;

	t1 = (aabb->min.x - ray->origin.x) * ray->inv_dir.x;
	t2 = (aabb->max.x - ray->origin.x) * ray->inv_dir.x;
	tnear = __builtin_fmin(t1, t2);
	tfar = __builtin_fmax(t1, t2);
	t1 = (aabb->min.y - ray->origin.y) * ray->inv_dir.y;
	t2 = (aabb->max.y - ray->origin.y) * ray->inv_dir.y;
	tnear = __builtin_fmax(tnear, __builtin_fmin(t1, t2));
	tfar = __builtin_fmin(tfar, __builtin_fmax(t1, t2));
	t1 = (aabb->min.z - ray->origin.z) * ray->inv_dir.z;
	t2 = (aabb->max.z - ray->origin.z) * ray->inv_dir.z;
	tnear = __builtin_fmax(tnear, __builtin_fmin(t1, t2));
	tfar = __builtin_fmin(tfar, __builtin_fmax(t1, t2));
	*tmin = tnear;
	*tmax = tfar;
	return (tfar >= 0.0 && tfar >= tnear);
}
