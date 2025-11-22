/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:51:17 by abdoali          ###   ########.fr       */
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
	
	/* AVX Optimization: Fill 8 floats (32 bytes) per instruction */
	/* 1e30f is our "infinity" / far plane */
	max_depth = _mm256_set1_ps(1e30f);
	
	i = 0;
	/* Unroll loop for AVX */
	while (i <= total - 8)
	{
		_mm256_storeu_ps(&z_buffer[i], max_depth);
		i += 8;
	}
	
	/* Handle remaining scalar tail (if size isn't multiple of 8) */
	while (i < total)
	{
		z_buffer[i] = 1e30f;
		i++;
	}
}

void	clear_image(t_graphics *g)
{
	int		i;
	int		total_bytes;
	char	*buffer;
	__m256i	zeros;

	/* Total size in bytes */
	total_bytes = g->window->height * g->window->main_img.img_line_len;
	buffer = g->window->main_img.img_addr;

	/* AVX Optimization: Fill 32 bytes (approx 8 pixels) per instruction */
	zeros = _mm256_setzero_si256();
	
	i = 0;
	/* Unroll loop for AVX */
	while (i <= total_bytes - 32)
	{
		_mm256_storeu_si256((__m256i *)&buffer[i], zeros);
		i += 32;
	}
	
	/* Handle remaining scalar tail */
	while (i < total_bytes)
	{
		buffer[i] = 0;
		i++;
	}
}