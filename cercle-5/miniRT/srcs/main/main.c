/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:57:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "debug.h"

/**
 * @brief Root dispatcher for the miniRT application run cycle.
 * @param path The scene file to execute.
 * @return int Exit code.
 */
static int	run_app(const char *path)
{
	void	*mlx;

	DBG_INFO_MSG(DBG_CH_RENDER, "Initializing MLX for: %s\n", path);
	mlx = mlx_init();
	if (!mlx)
	{
		DBG_ERR_MSG(DBG_CH_RENDER, "MLX init FAILED\n");
		ft_putendl_fd("Error: Failed to initialize MLX", STDERR_FILENO);
		return (1);
	}
	return (start_app(mlx, path));
}

/**
 * @brief Entry point for the miniRT raytracer.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return int Exit status.
 */
int	main(int ac, char **av)
{
	const char	*path;
	int			ret;

	DBG_LOG_INIT();
	DBG_INFO_MSG(DBG_CH_ALL, "=== miniRT start (v2026.03.26) ===\n");
	ft_putendl_fd("--- MINIRT STARTUP (v2026.03.26) ---", STDOUT_FILENO);
	setlocale(LC_NUMERIC, "C");
	path = "maps/rt/test2.rt";
	if (ac > 1)
		path = av[1];
	DBG_INFO_MSG(DBG_CH_ALL, "scene path: %s\n", path);
	ret = run_app(path);
	DBG_INFO_MSG(DBG_CH_ALL, "=== miniRT exit (code=%d) ===\n", ret);
	DBG_LOG_CLOSE();
	return (ret);
}
