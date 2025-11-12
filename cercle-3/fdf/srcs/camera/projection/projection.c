/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:24:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 23:44:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_point	project_point(t_vec3d p3d, int color, t_camera *cam, t_projection_type type,
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
