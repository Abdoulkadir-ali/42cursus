/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_clamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <math.h>

void	clamp_accel(t_physics_body *b)
{
	double	mag_sq;
	double	mag;

	mag_sq = vec3_mag_sq(b->accel);
	if (mag_sq > MAX_ACCEL * MAX_ACCEL)
	{
		mag = sqrt(mag_sq);
		b->accel = vec3_scale(b->accel, MAX_ACCEL / mag);
	}
}

void	clamp_speed(t_physics_body *b)
{
	double	mag_sq;
	double	mag;

	mag_sq = vec3_mag_sq(b->velocity);
	if (mag_sq > MAX_SPEED * MAX_SPEED)
	{
		mag = sqrt(mag_sq);
		b->velocity = vec3_scale(b->velocity, MAX_SPEED / mag);
	}
}
