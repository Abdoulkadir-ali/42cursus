/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:21:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_vec3d	rotate_x(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x;
	rotated.y = v.y * cos(angle) - v.z * sin(angle);
	rotated.z = v.y * sin(angle) + v.z * cos(angle);
	return (rotated);
}

t_vec3d	rotate_y(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x * cos(angle) + v.z * sin(angle);
	rotated.y = v.y;
	rotated.z = -v.x * sin(angle) + v.z * cos(angle);
	return (rotated);
}

t_vec3d	rotate_z(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x * cos(angle) - v.y * sin(angle);
	rotated.y = v.x * sin(angle) + v.y * cos(angle);
	rotated.z = v.z;
	return (rotated);
}

t_vec3d	apply_rotation(t_vec3d v, t_vec3d rot)
{
	t_vec3d	rotated;

	rotated = rotate_x(v, rot.x);
	rotated = rotate_y(rotated, rot.y);
	rotated = rotate_z(rotated, rot.z);
	return (rotated);
}

t_vec3d	apply_rotation_centered(t_vec3d v, t_vec3d rot, t_vec3d center)
{
	t_vec3d	centered;
	t_vec3d	rotated;

	centered.x = v.x - center.x;
	centered.y = v.y - center.y;
	centered.z = v.z - center.z;
	rotated = apply_rotation(centered, rot);
	rotated.x += center.x;
	rotated.y += center.y;
	rotated.z += center.z;
	return (rotated);
}
