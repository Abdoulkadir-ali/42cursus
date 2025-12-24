/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 02:50:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 03:19:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_camera	*init_camera_default(t_camera *cam)
{
	cam->rotation = create_vec3d(35.264, 0.0, 45.0);
	cam->offset = create_vec2d(0.0, 0.0);
	cam->grid_center = create_vec3d(0.0, 0.0, 0.0);
	cam->color_shift = create_vec3(0, 0, 0);
	cam->projection = PROJ_PARALLEL;
	cam->gui_style = GUI_STYLE_TRON_BLUE;
	cam->scale = 1.0;
	cam->target_scale = 1.0;
	cam->move_speed = 1.0;
	cam->zoom_speed = 1.0;
	cam->dampening_threshold = DEFAULT_DAMPENING_THRESHOLD;
	cam->pending_rot = create_vec2d(0.0, 0.0);
	cam->z_scale = 0.5;
	cam->frustum_margin = DEFAULT_FRUSTUM_MARGIN;
	cam->use_z_divisor = 1;
	cam->invert_movement = 1;
	cam->alpha = 90.0;
	cam->rotation_speed = DEFAULT_ROTATION_SPEED;
	cam->target_rotation = cam->rotation;
	return (cam);
}

t_camera_manager	*init_camera(t_camera_args args)
{
	t_camera_manager	*ctx;
	t_maps				*mgr;

	ctx = allocate_camera_manager(args);
	if (!ctx)
		return (NULL);
	if (!args.manager)
		return (ctx->map = args.map, ctx);
	mgr = args.manager;
	if (!setup_map_source(mgr, args))
		return (free(ctx->camera), free(ctx), NULL);
	ctx->map = mgr->current_map;
	update_rotation_matrix(ctx->camera);
	calculate_transform_matrix(ctx->camera);
	return (ctx);
}
