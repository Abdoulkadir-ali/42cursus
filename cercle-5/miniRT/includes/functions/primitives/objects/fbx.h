/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:58:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:48:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FBX_H
# define FBX_H

# include "mesh.h"

/* Prototypes */

bool					fbx_bin_build_mesh(t_fbx_bin *fbx);
void					fbx_build_flat(t_mesh *m, t_fbx_flat_params *p);
bool					fbx_setup_build(t_fbx_build *b, t_mesh *m,
							t_fbx_flat_params *p);
void					fbx_build_tris(t_fbx_build *b);
void					fbx_free_build(t_fbx_build *b);
void					ascii_load_normals(t_fbx_ascii *asc);
void					ascii_load_uvs(t_fbx_ascii *asc);
void					*read_fbx_array(int fd, size_t *count,
							size_t elem_sz);
void					read_offsets(int fd, t_fbx_bin_node *node,
							bool is_64bit);
void					read_node_header(int fd, t_fbx_bin_node *node,
							bool is_64bit);
void					parse_nodes(int fd, size_t end_offset, bool is_64,
							t_fbx_data *d);
t_fbx_bin_node			fbx_bin_node_binary_find(int fd, size_t end_offset,
							bool is_64, const char *target);
t_vec3					*repack_doubles_to_vec3(double *src, size_t count);
int						*repack_ints_to_ints(int *src, size_t count);
ssize_t					safe_read(int fd, void *buf, size_t count);

/* ASCII Parsing Helpers */
char					*find_node(char *p, char *end, const char *name);
char					*advance_to_data(char *p, char *end);
void					*parse_array(char **p, size_t *count, size_t sz,
							void (*f)(char **, void *));
void					f_vec2(char **p, void *dst);
void					f_vec3(char **p, void *dst);
void					f_int(char **p, void *dst);
char					*read_file_content(const char *path, size_t *out_size);
t_index					parse_texture(char *p, char *end, t_scene *scene,
							const char *fbx_path);
char					*resolve_fbx_path(const char *fbx_path,
							const char *tex_filename);
void					mesh_free(t_mesh *mesh);

/* FBX Specific (srcs/primitives/objects/parsing/) */
void					skip_properties(int fd, size_t num_props);
char					*fbx_next(char *p);

/* FBX Scene Addition (srcs/primitives/scene/add/objects/mesh/loaders/) */
bool					parse_fbx_worker(const char *path, t_scene *scene);
bool					parse_fbx_binary(const char *path,
							t_skinned_mesh *out);
bool					parse_fbx_ascii(const char *path, t_scene *scene,
							t_skinned_mesh *out);

#endif
