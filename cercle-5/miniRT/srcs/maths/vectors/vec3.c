/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 0.0});
}

t_vec3	vec3_pt(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 1.0});
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w});
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w});
}

t_vec3	vec3_scale(t_vec3 a, double s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s, a.w * s});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x, 0.0});
}

double	vec3_mag_sq(t_vec3 a)
{
	return (vec3_dot(a, a));
}

double	vec3_mag(t_vec3 a)
{
	return (sqrt(vec3_mag_sq(a)));
}

t_vec3	vec3_norm(t_vec3 a)
{
	double	mag;

	mag = vec3_mag(a);
	return (mag == 0 ? (t_vec3){0, 0, 0, 0} : vec3_scale(a, 1.0 / mag));
}

t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, double t)
{
	return (vec3_add(a, vec3_scale(vec3_sub(b, a), t)));
}

t_vec3	vec3_min(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z),
		fmin(a.w, b.w)});
}

t_vec3	vec3_max(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z),
		fmax(a.w, b.w)});
}

bool	vec3_compare(t_vec3 a, t_vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

void	vec3_orthonormal_basis(t_vec3 normal, t_vec3 *tangent,
		t_vec3 *bitangent)
{
	t_vec3	up;

	if (fabs(normal.y) > 0.9)
		up = vec3(1, 0, 0);
	else
		up = vec3(0, 1, 0);
	*bitangent = vec3_norm(vec3_cross(normal, up));
	*tangent = vec3_norm(vec3_cross(*bitangent, normal));
}

t_vec3	get_camera_forward(double pitch, double yaw)
{
	return (vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw)));
}

t_vec3	rotate_vector(t_vec3 v, double pitch, double yaw)
{
	double	y1;
	double	z1;
	t_vec3	v1;
	double	x2;
	double	y2;

	y1 = v.y * cos(pitch) - v.z * sin(pitch);
	z1 = v.y * sin(pitch) + v.z * cos(pitch);
	v1 = vec3(v.x, y1, z1);
	x2 = v1.x * cos(yaw) - v1.y * sin(yaw);
	y2 = v1.x * sin(yaw) + v1.y * cos(yaw);
	return (vec3(x2, y2, v1.z));
}
