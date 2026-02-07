/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/04 17:46:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "bvh.h"
#include "gui.h"
#include <stdio.h>


int	main(int ac, char **av)
{
	const char	*path;
	t_scene		*scene;
	t_bvh		*bvh;
	t_gui		*gui;

	if (ac > 1)
		path = av[1];
	else
		path = "maps/test2.rt";
	scene = parse_file(path);
	if (!scene)
	{
		fprintf(stderr, "Failed to load scene: %s\n", path);
		return (1);
	}
	bvh = bvh_create(scene);
	if (!bvh)
	{
		fprintf(stderr, "Failed to create BVH\n");
		destroy_scene(scene);
		return (1);
	}

	gui = gui_init(scene, bvh);
	if (!gui)
	{
		fprintf(stderr, "Failed to initialize GUI\n");
		bvh_destroy(bvh);
		destroy_scene(scene);
		return (1);
	}

	// gui_render(gui); // Removed to allow loop to handle it (Non-blocking)
	gui_loop(gui);

	gui_destroy(gui);
	bvh_destroy(bvh);
	destroy_scene(scene);
	return (0);
}
