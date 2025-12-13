/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:24:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:18:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static t_point	prepare_point(t_vec3d p3d, int color, t_camera *cam,
		double z_divisor)
{
	t_point	p;

	p.pos.x = p3d.x;
	p.pos.y = p3d.y;
	p.pos.z = p3d.z;
	p.color = color;
	if (cam->use_z_divisor && z_divisor != 0.0)
		p.pos.z /= z_divisor;
	p.pos.z *= cam->z_scale;
	return (p);
}

static t_point	select_projection(t_point p, t_camera *cam)
{
	t_projection_type	type;

	type = cam->projection;
	if (type == PROJ_ISOMETRIC)
		return (project_isometric(p, cam));
	else if (type == PROJ_ORTHOGRAPHIC)
		return (project_orthographic(p, cam));
	else if (type == PROJ_PERSPECTIVE)
		return (project_perspective(p, cam));
	else if (type == PROJ_OBLIQUE)
		return (project_oblique(p, cam));
	else if (type == PROJ_CAMERA_MATRIX)
		return (project_camera_matrix(p, cam));
	else if (type == PROJ_NONLINEAR)
		return (project_nonlinear(p, cam));
	return (project_isometric(p, cam));
}

t_point	project_point(t_vec3d p3d, int color, t_camera *cam, double z_divisor)
{
	t_point	p;

	if (p3d.z <= BAD_VALUE + 1.0)
		return ((t_point){.pos = {BAD_VALUE, BAD_VALUE, BAD_VALUE},
			.color = color});
	p = prepare_point(p3d, color, cam, z_divisor);
	return (select_projection(p, cam));
}
