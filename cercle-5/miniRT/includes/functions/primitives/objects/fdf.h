/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:30:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mesh.h"
# include "t_fdf.h"
# include "thread.h"

typedef struct s_fdf_uv_task
{
	t_mesh	*mesh;
	int		w;
	int		h;
	size_t	next_idx;
}	t_fdf_uv_task;

/* Prototypes */
bool					fdf_get_dimensions(const char *path, int *w, int *h);
void					fdf_fill_data(const char *path, t_mesh *mesh, int w,
							int h);
void					fdf_compute_normals(t_thread_pool *pool, t_mesh *mesh,
							int w, int h);
void					fdf_compute_uvs(t_thread_pool *pool, t_mesh *mesh,
							int w, int h);
void					fdf_triangulate(t_thread_pool *pool, t_mesh *mesh,
							int w, int h);
bool					fdf_init_mesh(t_mesh *mesh, int v_count, int i_count,
							const char *p);

/* FDF Scene Addition (srcs/primitives/scene/add/objects/mesh/loaders/) */
bool					parse_fdf_worker(const char *path, t_scene *scene);

#endif
