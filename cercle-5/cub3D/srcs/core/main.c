/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 03:16:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:30:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <time.h>

static bool	check_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
		safe_exit("Usage: ./cub3D <map.cub>\n", NULL, 1);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(argv[1] + len - 4, ".cub") != 0)
		safe_exit("Map file must have a .cub extension\n", NULL, 1);
	return (true);
}

int	main(int argc, char **argv)
{
	t_window	game;
	t_world		world;
	t_app		app;

	if (argc != 2 || !check_args(argc, argv))
		return (1);
	time(NULL);
	init_app(&app, &game, &world, argv[1]);
	mlx_loop(game.mlx);
	return (0);
}
