/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:48 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:37:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
# define PROJECTION_H

# include "vectors.h"
# include "map.h"

typedef enum e_projection_type
{
	PROJ_ISOMETRIC = 0,
	PROJ_ORTHOGRAPHIC,
	PROJ_PERSPECTIVE,
	PROJ_OBLIQUE,
	PROJ_CAMERA_MATRIX,
	PROJ_NONLINEAR,
	PROJ_COUNT
}	t_projection_type;

typedef struct s_camera	t_camera;
extern const char	*g_projection_names[PROJ_COUNT];

t_point	project_point(t_point p3d, t_camera cam, t_projection_type type,
			double z_divisor);
t_point	project_isometric(t_point p3d, t_camera cam);
t_point	project_orthographic(t_point p3d, t_camera cam);
t_point	project_perspective(t_point p3d, t_camera cam);
t_point	project_oblique(t_point p3d, t_camera cam);
t_point	project_camera_matrix(t_point p3d, t_camera cam);
t_point	project_nonlinear(t_point p3d, t_camera cam);

#endif
