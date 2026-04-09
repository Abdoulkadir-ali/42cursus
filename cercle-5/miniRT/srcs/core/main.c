/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "debug.h"
#include "thread.h"
#include <sys/stat.h>
#include <dirent.h>

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

	ft_print_debug("RUN_APP_START: path='%s'\n", path);
	mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (1);
	}
	scene = NULL;
	gui = init_app(path, &scene, mlx);
	return (start_gui(gui, scene, mlx));
}

static bool	is_rt_file(const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 4)
		return (false);
	return (ft_strcmp(name + len - 3, ".rt") == 0);
}

/*
** Scans dir for the first .rt file found. Caller must free the result.
*/
static char	*first_rt_in_dir(const char *dir)
{
	DIR				*d;
	struct dirent	*entry;
	char			*tmp;
	char			*result;

	d = opendir(dir);
	if (!d)
		return (NULL);
	result = NULL;
	entry = readdir(d);
	while (entry && !result)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
		{
			tmp = ft_strjoin(dir, "/");
			result = ft_strjoin(tmp, entry->d_name);
			free(tmp);
		}
		entry = readdir(d);
	}
	closedir(d);
	return (result);
}

static bool	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
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
