/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 02:50:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:13:54 by abdoali          ###   ########.fr       */
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

t_camera_manager	*init_camera(t_camera_args args)
{
	t_camera_manager	*ctx;
	t_camera			*cam;

	ctx = malloc(sizeof(t_camera_manager));
	if (!ctx)
		return (NULL);
	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	ctx->camera = init_camera_default(cam);
	ctx->window = args.window;
	/* Initialize map manager if provided; otherwise use provided map */
	if (args.manager)
	{
		t_maps *mgr = args.manager;
		/* If a single map filename was provided, load it into the manager
		   (replace any existing contents). Otherwise, if the manager already
		   contains a populated list (from init_map_list), preserve it. If the
		   manager is empty, fall back to creating a test grid. */
		if (args.map_file)
		{
			mgr->current_map = load_map(args.map_file);
			if (!mgr->current_map)
			{
				free(cam);
				free(ctx);
				return (NULL);
			}
			mgr->map_files = malloc(sizeof(char *));
			mgr->maps = malloc(sizeof(t_map *));
			if (mgr->map_files && mgr->maps)
			{
				mgr->map_files[0] = ft_strdup(args.map_file);
				mgr->maps[0] = mgr->current_map;
				mgr->count = 1;
				mgr->current_index = 0;
			}
			ctx->map = mgr->current_map;
		}
		else if (mgr->maps && mgr->count > 0)
		{
			/* manager already populated by caller (e.g. init_map_list) */
			mgr->current_index = 0;
			mgr->current_map = mgr->maps[mgr->current_index];
			ctx->map = mgr->current_map;
		}
		else
		{
			mgr->current_map = create_test_grid();
			if (!mgr->current_map)
			{
				free(cam);
				free(ctx);
				return (NULL);
			}
			mgr->map_files = NULL;
			mgr->maps = &mgr->current_map;
			mgr->count = 1;
			mgr->current_index = 0;
			ctx->map = mgr->current_map;
		}
	}
	else
	{
		ctx->map = args.map;
	}
	return (ctx);
}
