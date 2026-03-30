/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:21:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mesh.h"

typedef struct s_scene	t_scene;

typedef struct s_fdf
{
	t_mesh				*mesh;
	int					dims[2];
	int					row;
}						t_fdf;

typedef struct s_fdf_dim
{
	int					w;
	int					h;
}						t_fdf_dim;

/* Prototypes */
bool					parse_fdf(const char *path, t_mesh_resource *out);
bool					fdf_get_dimensions(const char *path, int *w, int *h);
void					fdf_fill_data(const char *path, t_mesh *mesh, int w,
							int h);
void					fdf_compute_normals(t_mesh *mesh, int w, int h);
void					fdf_compute_uvs(t_mesh *mesh, int w, int h);
void					fdf_triangulate(t_mesh *mesh, int w, int h);
bool					fdf_init_mesh(t_mesh *mesh, int v_count, int i_count,
							const char *p);

#endif
