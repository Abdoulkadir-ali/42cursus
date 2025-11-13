/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 02:50:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 14:35:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera	*init_camera_default(t_camera *cam)
{
	cam->rotation = create_vec3d(DEFAULT_CAMERA_ROTATION_X,
			DEFAULT_CAMERA_ROTATION_Y, DEFAULT_CAMERA_ROTATION_Z);
	cam->offset = create_vec2d(0.0, 0.0);
	cam->grid_center = create_vec3d(0.0, 0.0, 0.0);
	cam->color_shift = create_vec3(0, 0, 0);
	cam->projection = PROJ_ISOMETRIC;
	cam->gui_style = GUI_STYLE_TRON_BLUE;
	cam->scale = 1.0;
	cam->target_scale = 1.0;
	cam->move_speed = 1.0;
	cam->zoom_speed = 1.0;
	cam->dampening_threshold = DEFAULT_DAMPENING_THRESHOLD;
	cam->pending_rot = create_vec2d(0.0, 0.0);
	cam->z_scale = DEFAULT_Z_SCALE;
	cam->frustum_margin = DEFAULT_FRUSTUM_MARGIN;
	cam->spline_segments = DEFAULT_SPLINE_SEGMENTS;
	cam->use_z_divisor = 1;
	cam->invert_movement = 1;
	return (cam);
}

t_camera_context	*init_camera(t_camera_args args)
{
	t_camera_context	*ctx;
	t_camera			*cam;

	ctx = malloc(sizeof(t_camera_context));
	if (!ctx)
		return (NULL);
	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	ctx->camera = init_camera_default(cam);
	ctx->map = args.map;
	ctx->window = args.window;
	return (ctx);
}
