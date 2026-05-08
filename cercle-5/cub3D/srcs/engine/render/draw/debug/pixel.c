/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 04:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:32:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_debug_pixel(t_window *win, t_vec2i pi, float dist, t_vec3 color)
{
	int	idx;

	if (pi.x < 0 || pi.x >= win->width || pi.y < 0 || pi.y >= win->height)
		return ;
	idx = pi.y * win->width + pi.x;
	if (win->z_buffer && dist > win->z_buffer[idx] + 0.05f)
		return ;
	put_pixel(win, (t_vec2){(float)pi.x, (float)pi.y}, color);
}