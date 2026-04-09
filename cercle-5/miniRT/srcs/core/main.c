/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 18:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "debug.h"
#include "thread.h"

static void	cleanup(t_scene *scene, t_gui *gui)
{
	if (gui)
		gui_destroy(gui);
	else if (scene)
		destroy_scene(scene);
}

static t_gui	*init_app(const char *path, t_scene **scene, void *mlx)
{
	t_gui	*gui;

	*scene = parse_file(path, mlx);
	if (!*scene)
	{
		fprintf(stderr, "Failed to load scene: %s\n", path);
		return (NULL);
	}
	gui = gui_init(*scene, mlx);
	return (gui);
}

static int	run_app(const char *path)
{
	t_scene	*scene;
	t_gui	*gui;
	void	*mlx;

	ft_print_debug("RUN_APP_START: path='%s'\n", path);
	mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (1);
	}
	scene = NULL;
	gui = init_app(path, &scene, mlx);
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

int	main(int ac, char **av)
{
	const char	*path;
	char		*resolved;
	int			ret;

	ft_print_debug("---= MINIRT STARTUP =---\n");
	setlocale(LC_NUMERIC, "C");
	path = "maps/rt/test2.rt";
	if (ac > 1)
		path = av[1];
	resolved = NULL;
	if (is_directory(path))
	{
		resolved = first_rt_in_dir(path);
		if (!resolved)
		{
			fprintf(stderr, "No .rt files found in: %s\n", path);
			return (1);
		}
		path = resolved;
	}
	ret = run_app(path);
	free(resolved);
	return (ret);
}
