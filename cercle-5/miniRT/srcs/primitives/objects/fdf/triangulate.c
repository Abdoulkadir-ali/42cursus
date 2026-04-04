/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_triangulate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	*fdf_tri_worker(void *ptr)
{
	t_fdf_task	*task;
	int			p[2];
	int			idx;
	int			tri;

	task = (t_fdf_task *)ptr;
	while (1)
	{
		p[1] = __sync_fetch_and_add(&task->next_row, 1);
		if (p[1] >= task->h - 1)
			break ;
		p[0] = -1;
		while (++p[0] < task->w - 1)
		{
			idx = p[1] * task->w + p[0];
			tri = idx * 2; // Each quad has 2 triangles
			task->mesh->triangles[tri].v[0] = idx;
			task->mesh->triangles[tri].v[1] = idx + task->w;
			task->mesh->triangles[tri].v[2] = idx + 1;
			task->mesh->triangles[tri + 1].v[0] = idx + 1;
			task->mesh->triangles[tri + 1].v[1] = idx + task->w;
			task->mesh->triangles[tri + 1].v[2] = idx + task->w + 1;
		}
	}
	return (NULL);
}

void	fdf_triangulate(t_thread_pool *pool, t_mesh *mesh, int w, int h)
{
	t_fdf_task	task;

	task.mesh = mesh;
	task.w = w;
	task.h = h;
	task.next_row = 0;
	parallel_run(pool, task.h, fdf_tri_worker, &task);
}

