/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_projections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:23:49 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 18:42:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "projection.h"

t_point	project_oblique(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;
	double	oblique_angle;
	double	oblique_factor;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation_centered(v, cam.rotation, cam.grid_center);
	oblique_angle = 0.785398;
	oblique_factor = 0.5;
	p2d.pos.x = (rotated.x + rotated.y * cos(oblique_angle) * oblique_factor)
		* cam.scale;
	p2d.pos.y = (-rotated.z + rotated.y * sin(oblique_angle) * oblique_factor)
		* cam.scale;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}

t_point	project_camera_matrix(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;
	double	f;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation_centered(v, cam.rotation, cam.grid_center);
	f = 1.0 / tan(1.047 / 2.0);
	p2d.pos.x = (rotated.x * f / 1.333) * cam.scale * 10;
	p2d.pos.y = (rotated.z * f) * cam.scale * 10;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}

t_point	project_nonlinear(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation_centered(v, cam.rotation, cam.grid_center);
	p2d.pos.x = (rotated.x + sin(rotated.y * 0.05) * 5 - rotated.y)
		* cos(0.523599) * cam.scale;
	p2d.pos.y = ((rotated.x + rotated.y) * sin(0.523599) - rotated.z
			+ cos(rotated.x * 0.05) * 5) * cam.scale;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}
