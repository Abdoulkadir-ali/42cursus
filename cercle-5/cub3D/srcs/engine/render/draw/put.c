/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:09:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 05:52:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	flat_index(t_window *win, t_vec2 pos)
{
	int	index;

	index = (int)pos.y * win->line_len + (int)pos.x * (win->bpp / 8);
	return (index);
}

void	put_pixel(t_window *win, t_vec2 pos, t_vec3 color)
{
	char	*pixel;

	if (pos.x >= win->width || pos.y >= win->height || pos.x < 0.0f
		|| pos.y < 0.0f)
		return ;
	pixel = win->addr + flat_index(win, pos);
	pixel[0] = (char)color.z;
	pixel[1] = (char)color.y;
	pixel[2] = (char)color.x;
	if (win->bpp == 32)
		pixel[3] = 0;
}
