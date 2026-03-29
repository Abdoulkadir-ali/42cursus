/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 11:04:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "mesh.h"
#include "debug.h"

/**
 * @brief Performs graceful cleanup of GUI and Scene resources.
 * @param scene Pointer to the scene.
 * @param gui Pointer to the GUI context.
 */
static void	cleanup_app(t_scene *scene, t_gui *gui)
{
	if (gui && gui->win.mlx)
		gui_destroy(gui);
	else if (scene)
		destroy_scene(scene);
}

/**
 * @brief Loads the scene and initializes GUI data.
 * @param path Path to the .rt scene file.
 * @param gui Pointer to the stack-allocated GUI structure.
 * @param scene Output pointer for the loaded scene.
 * @param mlx Pointer to the MLX instance.
 * @return bool True on success, false on failure.
 */
static bool	load_scene(t_scene *scene, const char *path)
{
	const char	*ext;
	t_transform	t;

	ext = get_file_extension(path);
	if (ft_strcmp(ext, "rt") == 0)
		return (rt_load(scene, path));
	if (!load_mesh_file(scene, path))
		return (false);
	ft_memset(&t, 0, sizeof(t_transform));
	t.pos = vec3(0.0, 1.0, -4.0);
	t.forward = vec3(0.0, 0.0, 1.0);
	scene_apply_camera(scene, t, 70.0);
	return (true);
}

static bool	init_app(t_gui *gui, t_scene **scene, const char *path, void *mlx)
{
	DBG_INFO_MSG(DBG_CH_PARSER, "init_app: loading %s\n", path);
	*scene = create_scene(path);
	if (!*scene || !load_scene(*scene, path))
	{
		ft_putstr_fd("Error: Failed to load scene: ", STDERR_FILENO);
		ft_putendl_fd((char *)path, STDERR_FILENO);
		DBG_ERR_MSG(DBG_CH_PARSER, "init_app: scene load FAILED\n");
		if (*scene)
		{
			destroy_scene(*scene);
			*scene = NULL;
		}
		return (false);
	}
	DBG_INFO_MSG(DBG_CH_PARSER, "init_app: scene loaded, init GUI\n");
	return (gui_init(gui, *scene, mlx));
}

/**
 * @brief Starts the GUI engine and blocks until completion.
 * @param mlx Pointer to the MLX instance.
 * @param path Path to the .rt scene file.
 * @return int Exit status (0 for success, 1 for failure).
 */
int	start_app(void *mlx, const char *path)
{
	t_gui	gui;
	t_scene	*scene;

	ft_memset(&gui, 0, sizeof(t_gui));
	scene = NULL;
	if (!init_app(&gui, &scene, path, mlx))
	{
		ft_putendl_fd("Error: Failed to initialize GUI", STDERR_FILENO);
		cleanup_app(scene, &gui);
		return (1);
	}
	gui.win.mlx = mlx;
	DBG_INFO_MSG(DBG_CH_RENDER, "start_app: entering GUI loop\n");
	gui_loop(&gui);
	DBG_INFO_MSG(DBG_CH_RENDER, "start_app: GUI loop exited\n");
	cleanup_app(scene, &gui);
	return (0);
}
