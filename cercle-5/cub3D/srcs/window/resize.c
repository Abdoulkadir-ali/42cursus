/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 23:59:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <stdlib.h>

static void	rebuild_image(t_window *win)
{
	mlx_destroy_image(win->mlx, win->img);
	free(win->z_buffer);
	win->img = mlx_new_image(win->mlx, win->width, win->height);
	win->addr = mlx_get_data_addr(win->img, &win->bpp,
			&win->line_len, &win->endian);
	win->z_buffer = ft_calloc((size_t)win->width * win->height,
			sizeof(float));
}

void	handle_window_resize(t_window *win, int new_w, int new_h)
{
	if (!win || new_w <= 0 || new_h <= 0)
		return ;
	if (new_w == win->width && new_h == win->height)
		return ;
	win->width = new_w;
	win->height = new_h;
	rebuild_image(win);
}
