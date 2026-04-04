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

bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
		double *tmax)
{
	double	t1;
	double	t2;
	double	tn;
	double	tf;

	t1 = (aabb->min.x - ray->origin.x) * ray->inv_dir.x;
	t2 = (aabb->max.x - ray->origin.x) * ray->inv_dir.x;
	tn = (t1 < t2) ? t1 : t2;
	tf = (t1 > t2) ? t1 : t2;
	t1 = (aabb->min.y - ray->origin.y) * ray->inv_dir.y;
	t2 = (aabb->max.y - ray->origin.y) * ray->inv_dir.y;
	if (tn < ((t1 < t2) ? t1 : t2)) tn = ((t1 < t2) ? t1 : t2);
	if (tf > ((t1 > t2) ? t1 : t2)) tf = ((t1 > t2) ? t1 : t2);
	t1 = (aabb->min.z - ray->origin.z) * ray->inv_dir.z;
	t2 = (aabb->max.z - ray->origin.z) * ray->inv_dir.z;
	if (tn < ((t1 < t2) ? t1 : t2)) tn = ((t1 < t2) ? t1 : t2);
	if (tf > ((t1 > t2) ? t1 : t2)) tf = ((t1 > t2) ? t1 : t2);
	*tmin = tn;
	*tmax = tf;
	return (tf >= 0.0 && tf >= tn);
}
