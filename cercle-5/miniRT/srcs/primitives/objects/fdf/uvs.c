/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 01:34:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:42:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	*fdf_uv_worker(void *ptr)
{
	t_fdf_task	*t;
	size_t		i;
	size_t		j;
	size_t		total;

	t = (t_fdf_task *)ptr;
	total = (size_t)t->dims.x * (size_t)t->dims.y;
	while (1)
	{
		i = (size_t)__sync_fetch_and_add(&t->next_idx, 512);
		if (i >= total)
			break ;
		j = 0;
		while (j < 512 && i + j < total)
		{
			t->mesh->vertices[i + j].uv.x = (t->mesh->vertices[i + j].pos.x
					+ t->dims.x / 2.0) / (double)t->dims.x;
			t->mesh->vertices[i + j].uv.y = (t->mesh->vertices[i + j].pos.z
					+ t->dims.y * 0.5) / (double)t->dims.y;
			j++;
		}
	}
	return (NULL);
}

void	fdf_compute_uvs(t_thread_pool *pool, t_mesh *mesh, t_vec2 dims)
{
	t_fdf_task	task;

	task.mesh = mesh;
	task.dims = dims;
	task.next_idx = 0;
	parallel_run(pool, (size_t)dims.x * (size_t)dims.y, fdf_uv_worker, &task);
}
