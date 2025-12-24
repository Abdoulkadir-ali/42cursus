/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 03:19:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	init_manager_with_file(t_maps *mgr, char *map_file)
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

int	init_manager_with_test_grid(t_maps *mgr)
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

t_camera_manager	*allocate_camera_manager(t_camera_args args)
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
	if (ctx->window)
	{
		ctx->camera->offset.x = ctx->window->width / 2.0;
		ctx->camera->offset.y = ctx->window->height / 2.0;
	}
	return (ctx);
}

int	setup_map_source(t_maps *mgr, t_camera_args args)
{
	if (args.map_file)
	{
		if (is_directory(args.map_file))
			init_map_list(mgr, args.map_file);
		else if (!init_manager_with_file(mgr, args.map_file))
			return (0);
	}
	else if (mgr->maps && mgr->count > 0)
	{
		mgr->current_index = 0;
		mgr->current_map = mgr->maps[0];
	}
	else if (!init_manager_with_test_grid(mgr))
		return (0);
	return (1);
}
