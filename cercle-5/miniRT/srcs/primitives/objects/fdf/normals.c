/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:42:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vec3	fdf_vertex_normal(t_mesh *mesh, size_t x, size_t z, t_vec2 dims)
{
	size_t	idx;
	t_vec3	v[4];
	size_t	w;
	size_t	h;

	w = (size_t)dims.x;
	h = (size_t)dims.y;
	idx = z * w + x;
	v[0] = mesh->vertices[idx].pos;
	if (x > 0)
		v[0] = mesh->vertices[idx - 1].pos;
	v[1] = mesh->vertices[idx].pos;
	if (x < w - 1)
		v[1] = mesh->vertices[idx + 1].pos;
	v[2] = mesh->vertices[idx].pos;
	if (z > 0)
		v[2] = mesh->vertices[idx - w].pos;
	v[3] = mesh->vertices[idx].pos;
	if (z < h - 1)
		v[3] = mesh->vertices[idx + w].pos;
	return (vec3_norm(vec3(v[0].y - v[1].y, 2.0, v[2].y - v[3].y)));
}

static void	*fdf_normals_worker(void *ptr)
{
	t_fdf_task	*t;
	size_t		x;
	size_t		z;
	size_t		idx;

	t = (t_fdf_task *)ptr;
	while (1)
	{
		z = __sync_fetch_and_add(&t->next_row, 1);
		if (z >= (size_t)t->dims.y)
			break ;
		x = 0;
		while (x < (size_t)t->dims.x)
		{
			idx = z * (size_t)t->dims.x + x;
			t->mesh->vertices[idx].normal = fdf_vertex_normal(t->mesh,
					x, z, t->dims);
			x++;
		}
	}
	return (NULL);
}

void	fdf_compute_normals(t_thread_pool *pool, t_mesh *mesh, t_vec2 dims)
{
	t_fdf_task	task;

	task.mesh = mesh;
	task.dims = dims;
	task.next_row = 0;
	parallel_run(pool, (int)dims.y, fdf_normals_worker, &task);
}
