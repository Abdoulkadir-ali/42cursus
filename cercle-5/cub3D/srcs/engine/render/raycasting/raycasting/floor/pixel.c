/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:15:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_line_pixel(t_floor_data *d, int x, t_vec2 floor, t_texture *tex)
{
	t_vec2i	tx;

	tx.x = (int)(floor.x * tex->size.x) % tex->size.x;
	tx.y = (int)(floor.y * tex->size.y) % tex->size.y;
	if (tx.x < 0)
		tx.x += tex->size.x;
	if (tx.y < 0)
		tx.y += tex->size.y;
	((uint32_t *)(d->win->addr + d->y * d->win->line_len))[x] = tex->data[tx.y
		* tex->size.x + tx.x];
	if (d->win->z_buffer)
		d->win->z_buffer[d->y * d->win->width + x] = d->dist;
}
