/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vec3	fdf_vertex_normal(t_mesh *mesh, int x, int z, t_fdf_dim dim)
{
	int		idx;
	t_vec3	v[4];

	idx = z * dim.w + x;
	v[0] = mesh->vertices[idx].pos;
	if (x > 0)
		v[0] = mesh->vertices[idx - 1].pos;
	v[1] = mesh->vertices[idx].pos;
	if (x < dim.w - 1)
		v[1] = mesh->vertices[idx + 1].pos;
	v[2] = mesh->vertices[idx].pos;
	if (z > 0)
		v[2] = mesh->vertices[idx - dim.w].pos;
	v[3] = mesh->vertices[idx].pos;
	if (z < dim.h - 1)
		v[3] = mesh->vertices[idx + dim.w].pos;
	return (vec3_norm(vec3(v[0].y - v[1].y, 2.0, v[2].y - v[3].y)));
}

static void	*fdf_normals_worker(void *ptr)
{
	t_fdf_task	*task;
	int			x;
	int			z;
	int			idx;

	task = (t_fdf_task *)ptr;
	while (1)
	{
		z = __sync_fetch_and_add(&task->next_row, 1);
		if (z >= task->h)
			break ;
		x = -1;
		while (++x < task->w)
		{
			idx = z * task->w + x;
			task->mesh->vertices[idx].normal = fdf_vertex_normal(task->mesh,
					x, z, (t_fdf_dim){task->w, task->h});
		}
	}
	return (NULL);
}

void	fdf_compute_normals(t_thread_pool *pool, t_mesh *mesh, int w, int h)
{
	t_fdf_task	task;

	task.mesh = mesh;
	task.w = w;
	task.h = h;
	task.next_row = 0;
	parallel_run(pool, task.h, fdf_normals_worker, &task);
}
