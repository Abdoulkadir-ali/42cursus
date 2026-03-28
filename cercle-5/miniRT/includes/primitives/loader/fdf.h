/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:44:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_LOADER_H
# define FDF_LOADER_H

# include "material.h"
# include "mesh.h"
# include "parser.h"

/**
 * @brief Intermediate structure for FDF wireframe loading.
 * Stores point data before converting to scene Soak Mesh.
 */
typedef struct s_fdf
{
	int			width;
	int			height;
	double		*grid;
	t_mesh		mesh;
	const char	*path;
}				t_fdf;

/* --- PUBLIC API --- */
bool			fdf_load(t_scene *scene, const char *path);
bool			fdf_load_to_asset(t_fdf *f, const char *path);

/* --- MATERIAL PARSING & INJECTION --- */
/* FDF loader generates default wireframe materials as t_material structs.
 * Materials are injected via scene_add_material() from material/injection.c
 */

/* --- INTERNALS: injection --- */
bool			parse_fdf(t_scene *scene, t_parser *p);

/* --- INTERNALS: grid parsing --- */
bool			fdf_parse_grid_single_pass(t_fdf *f, t_parser *p);
bool			fdf_parse_dims(t_fdf *f, t_parser *p);
bool			fdf_fill_grid(t_fdf *f, t_parser *p);

/* --- INTERNALS: mesh generation --- */
bool			fdf_triangulate(t_fdf *f);
void			fdf_compute_normals(t_fdf *f);
void			fdf_gen_uvs(t_fdf *f);

#endif
