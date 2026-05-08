/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:11:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	render_fps_counter(t_window *win, t_world *world)
{
	char	fps_str[64];
	char	ms_str[64];
	int		color;

	color = 0x0000FF00;
	if (world->fps < 30)
		color = 0x00FFFF00;
	if (world->fps < 15)
		color = 0x00FF0000;
	ft_snprintf(fps_str, 64, "FPS: %d", (int)world->fps);
	ft_snprintf(ms_str, 64, "Frame: %d ms", (int)world->frame_time_ms);
	mlx_string_put(win->mlx, win->win, win->width - 150, 30, color, fps_str);
	mlx_string_put(win->mlx, win->win, win->width - 150, 50, color, ms_str);
}
