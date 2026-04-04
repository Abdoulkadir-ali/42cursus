/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 16:18:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "debug.h"
#include "thread.h"

/*
** Cleans up all resources.
*/
static void	cleanup(t_scene *scene, t_gui *gui)
{
	if (gui)
		gui_destroy(gui);
	else if (scene)
		destroy_scene(scene);
}

/*
** Initializes the application components.
** Loads the scene, builds the BVH, and initializes the GUI.
*/
static t_gui	*init_app(const char *path, t_scene **scene, void *mlx)
{
	t_gui	*gui;

	*scene = parse_file(path, mlx);
	if (!*scene)
	{
		fprintf(stderr, "Failed to load scene: %s\n", path);
		return (NULL);
	}
	(*scene)->bvh = bvh_create(*scene);
	if (!(*scene)->bvh)
	{
		fprintf(stderr, "Failed to create BVH\n");
		return (NULL);
	}
	gui = gui_init(*scene, mlx);
	return (gui);
}

static int	start_gui(t_gui *gui, t_scene *scene, void *mlx)
{
	if (!gui)
	{
		fprintf(stderr, "Failed to initialize GUI\n");
		cleanup(scene, NULL);
		return (1);
	}
	gui->win.mlx = mlx;
	gui_loop(gui);
	cleanup(scene, gui);
	return (0);
}

static int	run_app(const char *path)
{
	t_scene	*scene;
	t_gui	*gui;
	void	*mlx;

	printf("RUN_APP_START: path='%s'\n", path);
	fflush(stdout);
	ft_print_debug("DEBUG: Initializing MLX\n");
	mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (1);
	}
	scene = NULL;
	gui = init_app(path, &scene, mlx);
	ft_print_debug("DEBUG: Starting GUI\n");
	return (start_gui(gui, scene, mlx));
}

/*
** Main entry point.
** Parses arguments, initializes the application, and runs the GUI loop.
*/
int	main(int ac, char **av)
{
	const char	*path;

	printf("---= MINIRT STARTUP =---\n");
	fflush(stdout);
	setlocale(LC_NUMERIC, "C");
	path = "maps/rt/test2.rt";
	if (ac > 1)
		path = av[1];
	return (run_app(path));
}
