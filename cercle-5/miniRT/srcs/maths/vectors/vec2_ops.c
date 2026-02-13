/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2_scale(t_vec2 a, double s)
{
	return ((t_vec2){a.x * s, a.y * s});
}

double	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec2_mag_sq(t_vec2 a)
{
	return (vec2_dot(a, a));
}

double	vec2_mag(t_vec2 a)
{
	return (sqrt(vec2_mag_sq(a)));
}

t_vec2	vec2_norm(t_vec2 a)
{
	double	mag;

	mag = vec2_mag(a);
	if (mag == 0)
		return ((t_vec2){0, 0});
	return (vec2_scale(a, 1.0 / mag));
}
