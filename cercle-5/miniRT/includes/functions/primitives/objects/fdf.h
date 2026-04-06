/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:57:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mesh.h"
# include "t_fdf.h"
# include "thread.h"

typedef struct s_fdf_uv_task
{
	t_mesh				*mesh;
	t_vec2				dims;
	size_t				next_idx;
}						t_fdf_uv_task;

/* Prototypes */
bool					fdf_get_dimensions(const char *path, t_vec2 *dims);
void					fdf_fill_data(const char *path, t_mesh *mesh,
							t_vec2 dims);
void					fdf_compute_normals(t_thread_pool *pool, t_mesh *mesh,
							t_vec2 dims);
void					fdf_compute_uvs(t_thread_pool *pool, t_mesh *mesh,
							t_vec2 dims);
void					fdf_triangulate(t_thread_pool *pool, t_mesh *mesh,
							t_vec2 dims);
bool					fdf_init_mesh(t_mesh *mesh, size_t v_count,
							size_t i_count, const char *p);

/* Color/UV modes */
t_fdf_mode				fdf_detect_mode(const char *path);
void					fdf_apply_mode(t_mesh *mesh, t_scene *scene,
							t_vec2 dims, t_fdf_mode mode);

/* FDF Scene Addition (srcs/primitives/scene/add/objects/mesh/loaders/) */
bool					parse_fdf_worker(const char *path, t_scene *scene);

#endif
