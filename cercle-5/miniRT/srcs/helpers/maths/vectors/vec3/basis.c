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

/* vec3_orthonormal_basis is now static inline in maths.h */

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
