/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Reset the z-buffer to a large far-depth sentinel.
 * @param g Graphics state owning the z-buffer.
 */
void	clear_z_buffer(t_graphics *g)
{
	size_t	i;
	size_t	total;

	if (!g->window->z_buffer)
		return ;
	total = g->window->width * g->window->height;
	i = 0;
	while (i < total)
	{
		g->window->z_buffer[i] = 1.0e30f;
		i++;
	}
}

/**
 * @brief Clear the main image buffer to black.
 * @param g Graphics state owning the main image.
 */
void	clear_image(t_graphics *g)
{
	size_t	i;
	size_t	total_bytes;

	total_bytes = g->window->height * g->window->main_img.img_line_len;
	i = 0;
	while (i < total_bytes)
	{
		g->window->main_img.img_addr[i] = 0;
		i++;
	}
}

/**
 * @brief Clear all frame buffers that are active for the current render mode.
 * @param g Graphics state owning the frame buffers.
 */
void	clear_frame_buffers(t_graphics *g)
{
	if (g->window->main_img.img_addr)
		clear_image(g);
	if (g->render_config.use_depth_culling && g->window->z_buffer)
		clear_z_buffer(g);
}
