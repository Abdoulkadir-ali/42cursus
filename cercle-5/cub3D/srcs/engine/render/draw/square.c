/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:09:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/25 19:05:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_square(t_window *win, t_vec2 pos, float size, t_vec3 color)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (i < (size_t)size)
	{
		y = 0;
		while (y < (size_t)size)
		{
			put_pixel(win, (t_vec2){pos.x + (float)i, pos.y + (float)y}, color);
			y++;
		}
		i++;
	}
}
