/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:23:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	clear_z_buffer(t_graphics *g)
{
	size_t	i;
	size_t	total;

	if (!g->window->z_buffer)
		return ;
	total = g->window->width * g->window->height;
	i = 0;
	while (i < total)
		g->window->z_buffer[i++] = 1.0e30f;
}

void	clear_image(t_graphics *g)
{
	size_t	total_bytes;

	if (!g->window->main_img.img_addr)
		return ;
	total_bytes = g->window->height * g->window->main_img.img_line_len;
	ft_bzero(g->window->main_img.img_addr, total_bytes);
}

void	clear_frame_buffers(t_graphics *g)
{
	if (g->window->main_img.img_addr)
		clear_image(g);
	if (g->render_config.use_depth_culling && g->window->z_buffer)
		clear_z_buffer(g);
}
