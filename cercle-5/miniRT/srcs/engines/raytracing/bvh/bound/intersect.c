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

static double	min_double(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

static double	max_double(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
		double *tmax)
{
	double	t1;
	double	t2;

	t1 = (aabb->min.x - ray->origin.x) * ray->inv_dir.x;
	t2 = (aabb->max.x - ray->origin.x) * ray->inv_dir.x;
	*tmin = min_double(t1, t2);
	*tmax = max_double(t1, t2);
	t1 = (aabb->min.y - ray->origin.y) * ray->inv_dir.y;
	t2 = (aabb->max.y - ray->origin.y) * ray->inv_dir.y;
	*tmin = max_double(*tmin, min_double(t1, t2));
	*tmax = min_double(*tmax, max_double(t1, t2));
	t1 = (aabb->min.z - ray->origin.z) * ray->inv_dir.z;
	t2 = (aabb->max.z - ray->origin.z) * ray->inv_dir.z;
	*tmin = max_double(*tmin, min_double(t1, t2));
	*tmax = min_double(*tmax, max_double(t1, t2));
	return (*tmax >= 0.0 && *tmax >= *tmin);
}
