/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:55:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:55:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

float	axis_val(t_vec3 v, int a)
{
	if (a == 0)
		return (v.x);
	if (a == 1)
		return (v.y);
	return (v.z);
}

int	pick_axis(t_aabb cb, float *kk, float *bmin)
{
	t_vec3	d;
	int		axis;

	d = v3_sub(cb.max, cb.min);
	axis = 0;
	if (d.y > d.x && d.y >= d.z)
		axis = 1;
	else if (d.z > d.x && d.z > d.y)
		axis = 2;
	*bmin = axis_val(cb.min, axis);
	*kk = (SAH_BINS * 0.999f) / fmaxf(1e-20f, axis_val(d, axis));
	return (axis);
}
