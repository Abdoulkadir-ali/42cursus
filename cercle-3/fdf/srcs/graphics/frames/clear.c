/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:12:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>
#include <pthread.h>

void	clear_z_buffer(t_graphics *g)
{
	t_clear_z_ctx	ctx;

	if (!g->window->z_buffer)
		return ;
	ctx.total = g->window->width * g->window->height;
	ctx.z_buffer = g->window->z_buffer;
	ctx.max_depth = _mm256_set1_ps(1e30f);
	clear_z_buffer_simd(&ctx);
	clear_z_buffer_remainder(&ctx);
}

void	clear_image(t_graphics *g)
{
	t_clear_img_ctx	ctx;

	ctx.total_bytes = g->window->height * g->window->main_img.img_line_len;
	ctx.buffer = g->window->main_img.img_addr;
	ctx.zeros = _mm256_setzero_si256();
	clear_image_simd(&ctx);
	clear_image_remainder(&ctx);
}

static void	*thread_clear_routine(void *data)
{
	t_thread_data	*t;
	t_graphics		*g;
	size_t			rows;
	int				line_len;
	t_clear_img_ctx	img_ctx;
	t_clear_z_ctx	z_ctx;

	t = (t_thread_data *)data;
	g = t->g;
	rows = t->end_y - t->start_y;
	line_len = g->window->main_img.img_line_len;

	// Clear Image Chunk
	img_ctx.buffer = g->window->main_img.img_addr + (t->start_y * line_len);
	img_ctx.total_bytes = rows * line_len;
	img_ctx.zeros = _mm256_setzero_si256();
	img_ctx.i = 0;
	clear_image_simd(&img_ctx);
	clear_image_remainder(&img_ctx);

	// Clear Z Buffer Chunk
	if (g->window->z_buffer)
	{
		z_ctx.z_buffer = g->window->z_buffer + (t->start_y * g->window->width);
		z_ctx.total = rows * g->window->width;
		z_ctx.max_depth = _mm256_set1_ps(1e30f);
		z_ctx.i = 0;
		clear_z_buffer_simd(&z_ctx);
		clear_z_buffer_remainder(&z_ctx);
	}
	return (NULL);
}

void	clear_frame_buffers(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	args[NUM_THREADS];
	int				step;
	int				i;

	step = g->window->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i].g = g;
		args[i].start_y = i * step;
		if (i == NUM_THREADS - 1)
			args[i].end_y = g->window->height;
		else
			args[i].end_y = (i + 1) * step;
		pthread_create(&threads[i], NULL, thread_clear_routine, &args[i]);
		i++;
	}
	join_threads(threads);
}
