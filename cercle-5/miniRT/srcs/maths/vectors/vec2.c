/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_pt(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}

t_vec2	vec2_mul(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x * b.x, a.y * b.y});
}

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
	return (mag == 0 ? (t_vec2){0, 0} : vec2_scale(a, 1.0 / mag));
}
