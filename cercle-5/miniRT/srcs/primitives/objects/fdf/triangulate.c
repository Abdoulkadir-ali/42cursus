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

static void	fdf_tri_cell(t_mesh *mesh, size_t x, size_t z, t_vec2s dims)
{
	size_t	idx;
	size_t	tri;

	idx = z * dims.x + x;
	tri = (z * (dims.x - 1) + x) * 2;
	mesh->indices[tri * 3 + 0] = idx;
	mesh->indices[tri * 3 + 1] = idx + dims.x;
	mesh->indices[tri * 3 + 2] = idx + 1;
	mesh->indices[(tri + 1) * 3 + 0] = idx + 1;
	mesh->indices[(tri + 1) * 3 + 1] = idx + dims.x;
	mesh->indices[(tri + 1) * 3 + 2] = idx + dims.x + 1;
}

static void	*fdf_tri_worker(void *ptr)
{
	t_fdf_task	*t;
	size_t		x;
	size_t		z;

	t = (t_fdf_task *)ptr;
	while (1)
	{
		z = __sync_fetch_and_add(&t->next_row, 1);
		if (z >= t->dims.y - 1)
			break ;
		x = 0;
		while (x < t->dims.x - 1)
			fdf_tri_cell(t->mesh, x++, z, t->dims);
	}
	return (NULL);
}

void	fdf_triangulate(t_thread_pool *pool, t_mesh *mesh, t_vec2s dims)
{
	t_fdf_task	task;

	task.mesh = mesh;
	task.dims = dims;
	task.next_row = 0;
	parallel_run(pool, dims.y - 1, fdf_tri_worker, &task);
}
