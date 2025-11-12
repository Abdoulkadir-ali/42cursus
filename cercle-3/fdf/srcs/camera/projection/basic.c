/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:22:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:49:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"


t_point	project_isometric(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation_centered(v, cam.rotation, cam.grid_center);
	p2d.pos.x = (rotated.x - rotated.y) * cos(0.523599) * cam.scale;
	p2d.pos.y = (rotated.x + rotated.y) * sin(0.523599) * cam.scale
		- rotated.z * cam.scale;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}

t_point	project_orthographic(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation_centered(v, cam.rotation, cam.grid_center);
	p2d.pos.x = rotated.x * cam.scale;
	p2d.pos.y = -rotated.z * cam.scale;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}

t_point	project_perspective(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;
	double	perspective_factor;
	double	depth;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation_centered(v, cam.rotation, cam.grid_center);
	depth = rotated.y + 200;
	if (depth < 1)
		depth = 1;
	perspective_factor = 500.0 / depth;
	p2d.pos.x = rotated.x * cam.scale * perspective_factor;
	p2d.pos.y = -rotated.z * cam.scale * perspective_factor;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}
