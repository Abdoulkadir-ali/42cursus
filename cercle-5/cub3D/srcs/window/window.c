/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 02:44:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 15:26:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	init_window(t_window *game)
{
	game->width = WINDOW_WIDTH;
	game->height = WINDOW_HEIGHT;
	game->title = "Cub3D";
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height,
			game->title);
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len,
			&game->endian);
	game->z_buffer = (float *)ft_calloc((size_t)game->width * game->height,
			sizeof(float));
	game->mm_cell = 8;
	game->mm_margin = 10;
}

void	render_window(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
}
