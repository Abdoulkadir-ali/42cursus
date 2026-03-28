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

static inline double	ft_dmin(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

static inline double	ft_dmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * Fast AABB intersection test using the slabs method.
 * Uses ft_dmin/ft_dmax instead of fmin/fmax to avoid undefined behaviour
 * with NaN under -ffast-math / -ffinite-math-only.
 */
bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
		double *tmax)
{
	double	t1;
	double	t2;

	t1 = (aabb->min[0] - ray->origin.x) * ray->inv_dir.x;
	t2 = (aabb->max[0] - ray->origin.x) * ray->inv_dir.x;
	*tmin = ft_dmin(t1, t2);
	*tmax = ft_dmax(t1, t2);
	t1 = (aabb->min[1] - ray->origin.y) * ray->inv_dir.y;
	t2 = (aabb->max[1] - ray->origin.y) * ray->inv_dir.y;
	*tmin = ft_dmax(*tmin, ft_dmin(t1, t2));
	*tmax = ft_dmin(*tmax, ft_dmax(t1, t2));
	t1 = (aabb->min[2] - ray->origin.z) * ray->inv_dir.z;
	t2 = (aabb->max[2] - ray->origin.z) * ray->inv_dir.z;
	*tmin = ft_dmax(*tmin, ft_dmin(t1, t2));
	*tmax = ft_dmin(*tmax, ft_dmax(t1, t2));
	return (*tmax >= 0 && *tmax >= *tmin);
}
