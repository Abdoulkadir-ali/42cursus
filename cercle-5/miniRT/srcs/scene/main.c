/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 17:45:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "gui.h"

/*
** Cleans up all resources.
*/
static void	cleanup(t_scene *scene, t_bvh *bvh, t_gui *gui)
{
	if (gui)
		gui_destroy(gui);
	if (bvh)
		bvh_destroy(bvh);
	if (scene)
		destroy_scene(scene);
}

/*
** Initializes the application components.
** Loads the scene, builds the BVH, and initializes the GUI.
*/
static t_gui	*init_app(const char *path, t_scene **scene, t_bvh **bvh, void *mlx)
{
	*scene = parse_file(path, mlx);
	if (!*scene)
	{
		fprintf(stderr, "Failed to load scene: %s\n", path);
		return (NULL);
	}
	*bvh = bvh_create(*scene);
	if (!*bvh)
	{
		fprintf(stderr, "Failed to create BVH\n");
		return (NULL);
	}
	return (gui_init(*scene, *bvh, mlx));
}

/*
** Main entry point.
** Parses arguments, initializes the application, and runs the GUI loop.
*/
int	main(int ac, char **av)
{
	const char	*path;
	t_scene		*scene;
	t_bvh		*bvh;
	t_gui		*gui;

	path = "maps/rt/test2.rt";
	if (ac > 1)
		path = av[1];
	ft_print_debug("DEBUG: Starting miniRT with map: %s\n", path);
	/* Initialize MLX early for texture loading */
	void *mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (1);
	}

	scene = NULL;
	bvh = NULL;
	gui = init_app(path, &scene, &bvh, mlx);
	if (!gui)
	{
		fprintf(stderr, "Failed to initialize GUI\n");
		cleanup(scene, bvh, NULL);
		return (1);
	}
	gui->win.mlx = mlx; /* Store it in gui */
	gui_loop(gui);
	cleanup(scene, bvh, gui);
	return (0);
}
