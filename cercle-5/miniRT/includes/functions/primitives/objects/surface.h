/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:34:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 11:05:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SURFACE_H
# define SURFACE_H

# include "helpers.h"
# include "types.h"
# include "parser.h"

/* Function Prototypes (srcs/objects/surface/) */
t_material				*create_material(t_material material);
void					apply_magic_colors(t_material *m, t_vec3 color);
void					apply_more_magic_colors(t_material *m, t_vec3 color);
void					convert_rgba_to_bgra(unsigned char *data, int size);
void					init_texture_props(t_texture *tex, int w, int h,
							char *data);
bool					load_texture_from_memory(t_texture *tex,
							unsigned char *buffer, int size);
bool					load_texture(void *mlx_ptr, t_texture *tex,
							const char *path);
bool					load_xpm(void *mlx_ptr, t_texture *tex,
							const char *path);
bool					load_stbi(t_texture *tex, const char *path);
t_vec3					sample_texture(t_texture *tex, double u, double v);
/* Texture Loading (srcs/objects/surface/texture/) */
bool					load_texture_xpm(void *mlx_ptr, t_texture *tex,
							const char *path);

/* Material Scene Addition (srcs/primitives/scene/add/material/) */
t_index					scene_add_material(t_scene *scene, t_vec3 color);
t_index					scene_add_fresh_material(t_scene *scene, t_vec3 color);
t_index					scene_clone_material(t_scene *scene, size_t src_id);
size_t					scene_add_checker_material(t_scene *scene, t_vec3 a,
							t_vec3 b, double scale);
t_index					scene_find_material(t_scene *scene, const char *name);
t_index					scene_add_named_material(t_scene *scene,
							const char *name);void						scene_init_uv_flags(t_scene *scene);
#endif
