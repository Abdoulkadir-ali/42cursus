/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

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
