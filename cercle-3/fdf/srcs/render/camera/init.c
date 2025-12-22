/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 02:50:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:14:34 by abdoali          ###   ########.fr       */
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

static int	init_manager_with_file(t_maps *mgr, char *map_file)
{
	mgr->current_map = load_map(map_file);
	if (!mgr->current_map)
		return (0);
	mgr->map_files = malloc(sizeof(char *));
	mgr->maps = malloc(sizeof(t_map *));
	if (!mgr->map_files || !mgr->maps)
	{
		if (mgr->map_files)
			free(mgr->map_files);
		if (mgr->maps)
			free(mgr->maps);
		return (0);
	}
	mgr->map_files[0] = ft_strdup(map_file);
	mgr->maps[0] = mgr->current_map;
	mgr->count = 1;
	mgr->current_index = 0;
	return (1);
}

static int	init_manager_with_test_grid(t_maps *mgr)
{
	mgr->current_map = create_test_grid();
	if (!mgr->current_map)
		return (0);
	mgr->map_files = NULL;
	mgr->maps = &mgr->current_map;
	mgr->count = 1;
	mgr->current_index = 0;
	return (1);
}

static t_camera_manager	*allocate_camera_manager(t_camera_args args)
{
	t_camera_manager	*ctx;
	t_camera			*cam;

	ctx = malloc(sizeof(t_camera_manager));
	if (!ctx)
		return (NULL);
	cam = malloc(sizeof(t_camera));
	if (!cam)
	{
		free(ctx);
		return (NULL);
	}
	ctx->camera = init_camera_default(cam);
	ctx->window = args.window;
	// Initialize offset to screen center
	if (ctx->window)
	{
		ctx->camera->offset.x = ctx->window->width / 2.0;
		ctx->camera->offset.y = ctx->window->height / 2.0;
	}
	return (ctx);
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
	if (args.map_file)
	{
		if (!init_manager_with_file(mgr, args.map_file))
			return (free(ctx->camera), free(ctx), NULL);
	}
	else if (mgr->maps && mgr->count > 0)
	{
		mgr->current_index = 0;
		mgr->current_map = mgr->maps[0];
	}
	else if (!init_manager_with_test_grid(mgr))
		return (free(ctx->camera), free(ctx), NULL);
	ctx->map = mgr->current_map;
	return (ctx);
}
