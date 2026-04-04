/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_uvs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_fdf_uv_task
{
	t_mesh	*mesh;
	int		w;
	int		h;
	size_t	next_idx;
}	t_fdf_uv_task;

static void	*fdf_uv_worker(void *ptr)
{
	t_fdf_uv_task	*task;
	int				i;

	task = (t_fdf_uv_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&task->next_idx, 512);
		if (i >= task->w * task->h)
			break ;
		for (int j = 0; j < 512 && i + j < task->w * task->h; j++)
		{
			task->mesh->vertices[i+j].uv.x = (task->mesh->vertices[i+j].pos.x 
				+ task->w / 2.0) / (double)task->w;
			task->mesh->vertices[i+j].uv.y = (task->mesh->vertices[i+j].pos.z 
				+ task->h / 2.0) / (double)task->h;
		}
	}
	return (NULL);
}

void	fdf_compute_uvs(t_thread_pool *pool, t_mesh *mesh, int w, int h)
{
	t_fdf_uv_task	task;

	task.mesh = mesh;
	task.w = w;
	task.h = h;
	task.next_idx = 0;
	parallel_run(pool, (size_t)w * (size_t)h, fdf_uv_worker, &task);
}
