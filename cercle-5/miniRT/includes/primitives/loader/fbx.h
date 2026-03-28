/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:52:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FBX_LOADER_H
# define FBX_LOADER_H

# include "parser.h"
# include "scene.h"
# include "material.h"
# include "animations.h"

/* --- FBX LOADER STRUCTURE --- */
typedef struct s_fbx
{
	t_mesh		*meshes;
	int			mesh_count;
	t_animation	*animations;
	int			anim_count;
	t_material	*materials;
	int			mat_count;
	const char	*path;
	uint32_t	version;
	int			fd;
	bool		is_64;
	double		*v;
	uint32_t	vc;
	int			*ri;
	uint32_t	rc;
	double		*vn;
	uint32_t	nc;
	double		*vu;
	uint32_t	uc;
}				t_fbx;

/* --- BINARY PARSING INTERNALS: Array --- */
typedef struct s_fbx_array
{
	char		type;
	uint32_t	actual_sz;
	uint32_t	arr_len;
	uint32_t	encoding;
	uint32_t	comp_len;
}				t_fbx_array;

/* --- BINARY PARSING INTERNALS: Node --- */
typedef struct s_fbx_bin_node
{
	uint64_t	end_offset;
	uint64_t	num_properties;
	uint64_t	property_list_len;
	uint8_t		name_len;
	char		name[256];
}				t_fbx_bin_node;

/* --- BINARY INJECTION INTERNALS: Build context --- */
typedef struct s_fbx_flat_args
{
	int		*raw;
	int		raw_c;
	t_vec3	*n;
	int		nc;
	t_vec2	*u;
	int		uc;
	int		vc;
}				t_fbx_flat_args;

typedef struct s_fbx_build
{
	t_mesh	*m;
	int		*raw;
	int		raw_c;
	t_vec3	*n;
	int		nc;
	t_vec2	*u;
	int		uc;
	int		vc;
	int		tc;
	int		ps;
	int		vp;
	t_vec3	*nv;
	t_vec3	*nn;
	t_vec2	*nu;
	int		*ni;
	int		*v;
	int		use_v_n;
	int		use_v_u;
}				t_fbx_build;

/* --- BINARY INJECTION INTERNALS: Functions --- */
bool			fbx_setup_build(t_fbx_build *b, t_mesh *m, t_fbx_flat_args *p);
void			fbx_build_tris(t_fbx_build *b);
void			fbx_free_build(t_fbx_build *b);

/* --- PUBLIC API --- */
bool			fbx_load(t_scene *scene, const char *path);
bool			fbx_load_to_asset(t_fbx *f, const char *path);
bool			parse_fbx_entry(t_scene *scene, t_parser *p);
bool			parse_fbx(t_scene *scene, t_parser *p);

/* --- MATERIAL PARSING & INJECTION --- */
/* FBX loader parses materials as t_material structs.
 * Materials are injected via scene_add_material() from material/injection.c
 */

/* --- INTERNALS --- */
bool			fbx_is_binary(int fd);
bool			fbx_parse_binary(t_fbx *f);
bool			fbx_parse_ascii(t_fbx *f);
void			fbx_clear_asset(t_fbx *f);
char			*fbx_read_file(const char *path, size_t *out_size);
char			*fbx_find_node(char *start, char *end, const char *key);

/* --- BINARY PARSING INTERNALS: Functions --- */
void			*read_fbx_array(int fd, uint32_t *count, size_t elem_sz);
void			*fbx_convert_array(t_fbx_array *a, void *uncomp,
					size_t elem_sz, uint32_t *count);
void			fbx_parse_nodes(t_fbx *f, uint64_t end);
bool			fbx_build_mesh(t_fbx *f);
void			fbx_read_header(int fd, t_fbx_bin_node *n, bool is_64);
void			fbx_skip_props(int fd, uint64_t num);
t_vec3			*fbx_repack_vec3(double *raw, uint32_t v_count);
void			*fbx_parse_array_ascii(char **p, uint32_t *count, size_t elem_sz);

/* --- INJECTION (Scene add functions) --- */
bool			scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
