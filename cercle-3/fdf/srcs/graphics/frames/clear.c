/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:10:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>

void	clear_z_buffer(t_graphics *g)
{
	int		i;
	int		total;
	float	*z_buffer;
	__m256	max_depth;

	if (!g->window->z_buffer)
		return ;
	total = g->window->width * g->window->height;
	z_buffer = g->window->z_buffer;
	max_depth = _mm256_set1_ps(1e30f);
	i = 0;
	while (i <= total - 8)
	{
		_mm256_storeu_ps(&z_buffer[i], max_depth);
		i += 8;
	}
	while (i < total)
		z_buffer[i++] = 1e30f;
}

void	clear_image(t_graphics *g)
{
	int i;
	int total_bytes;
	char *buffer;
	__m256i zeros;

	total_bytes = g->window->height * g->window->main_img.img_line_len;
	buffer = g->window->main_img.img_addr;
	zeros = _mm256_setzero_si256();

	i = 0;
	while (i <= total_bytes - 32)
	{
		_mm256_storeu_si256((__m256i *)&buffer[i], zeros);
		i += 32;
	}
	while (i < total_bytes)
		buffer[i++] = 0;
}