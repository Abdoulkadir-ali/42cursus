/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:24:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:49:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_point	project_point(t_point p3d, t_camera cam, t_projection_type type,
		double z_divisor)
{
	if (cam.use_z_divisor && z_divisor != 0.0)
		p3d.pos.z /= z_divisor;
	p3d.pos.z *= cam.z_scale;
	if (type == PROJ_ISOMETRIC)
		return (project_isometric(p3d, cam));
	else if (type == PROJ_ORTHOGRAPHIC)
		return (project_orthographic(p3d, cam));
	else if (type == PROJ_PERSPECTIVE)
		return (project_perspective(p3d, cam));
	else if (type == PROJ_OBLIQUE)
		return (project_oblique(p3d, cam));
	else if (type == PROJ_CAMERA_MATRIX)
		return (project_camera_matrix(p3d, cam));
	else if (type == PROJ_NONLINEAR)
		return (project_nonlinear(p3d, cam));
	return (project_isometric(p3d, cam));
}
