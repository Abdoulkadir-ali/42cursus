/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   fdf_uvs.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abdoali <abdoali@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/12 12:00:00 by abdoali		   #+#	#+#			 */
/*   Updated: 2026/02/12 12:00:00 by abdoali		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

static void	*fdf_uv_worker(void *ptr)
{
	t_fdf_uv_task	*t;
	int				i;
	int				j;

	t = (t_fdf_uv_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&t->next_idx, 512);
		if (i >= t->w * t->h)
			break ;
		j = 0;
		while (j < 512 && i + j < t->w * t->h)
		{
			t->mesh->vertices[i + j].uv.x = (t->mesh->vertices[i + j].pos.x
					+ t->w / 2.0) / (double)t->w;
			t->mesh->vertices[i + j].uv.y = (t->mesh->vertices[i + j].pos.z
					+ t->h / 2.0) / (double)t->h;
			j++;
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
