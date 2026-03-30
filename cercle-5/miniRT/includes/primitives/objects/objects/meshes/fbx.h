/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:58:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 21:06:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FBX_H
# define FBX_H

# include "mesh.h"
# include "../../parser/parser.h"

typedef struct s_scene	t_scene;

typedef struct s_fbx_bin_node
{
	uint64_t			end_offset;
	uint64_t			num_properties;
	uint64_t			property_list_len;
	uint8_t				name_len;
	char				name[1024];
}						t_fbx_bin_node;

typedef struct s_fbx_data
{
	t_vec3				*v;
	uint32_t			vc;
	int					*ri;
	uint32_t			rc;
	t_vec3				*vn;
	uint32_t			nc;
	t_vec2				*vu;
	uint32_t			uc;
}						t_fbx_data;

typedef struct s_fbx_flat_params
{
	int					*raw;
	int					raw_c;
	t_vec3				*n;
	int					nc;
	t_vec2				*u;
	int					uc;
	int					vc;
}						t_fbx_flat_params;

typedef struct s_fbx_build
{
	t_mesh				*m;
	int					*raw;
	int					raw_c;
	t_vec3				*n;
	int					nc;
	t_vec2				*u;
	int					uc;
	int					vc;
	int					tc;
	t_vec3				*nv;
	t_vec3				*nn;
	t_vec2				*nu;
	int					*ni;
	int					*v;
	int					vp;
	int					ps;
	int					use_v_n;
	int					use_v_u;
}						t_fbx_build;

typedef struct s_fbx_parse
{
	int					fd;
	bool				is_64;
	t_fbx_data			*d;
}						t_fbx_parse;

typedef struct s_fbx_array_req
{
	const char			*label;
	void				**dst;
	uint32_t			*count;
	size_t				elem_sz;
	uint32_t			div;
}						t_fbx_array_req;

typedef struct s_fbx_array
{
	uint32_t			arr_len;
	uint32_t			encoding;
	uint32_t			comp_len;
	size_t				actual_sz;
	char				type;
}						t_fbx_array;

typedef struct s_fbx_bin
{
	int					fd;
	uint32_t			version;
	t_skinned_mesh		mesh;
	t_fbx_data			data;
}						t_fbx_bin;

typedef struct s_fbx_buf
{
	char				*buf;
	size_t				cap;
	size_t				len;
}						t_fbx_buf;

typedef struct s_fbx_ascii
{
	t_skinned_mesh		mesh;
	t_vec3				*rn;
	t_vec2				*ru;
	int					*ri;
	int					rc;
	int					vc;
	int					nc;
	int					uc;
	char				*buf;
	char				*p;
	char				*end;
	size_t				buf_size;
	int					mat_id;
	const char			*path;
}						t_fbx_ascii;

/* Prototypes */
bool					parse_fbx(const char *path, t_mesh_resource *out,
							void *mlx_ptr);
bool					parse_fbx_ascii(const char *path, t_mesh_resource *out,
							void *mlx_ptr);
bool					parse_fbx_binary(const char *path, t_mesh_resource *out,
							void *mlx_ptr);
bool					fbx_bin_build_mesh(t_fbx_bin *fbx);
void					fbx_build_flat(t_mesh *m, t_fbx_flat_params *p);
bool					fbx_setup_build(t_fbx_build *b, t_mesh *m,
							t_fbx_flat_params *p);
void					fbx_build_tris(t_fbx_build *b);
void					fbx_free_build(t_fbx_build *b);
void					ascii_load_normals(t_fbx_ascii *asc);
void					ascii_load_uvs(t_fbx_ascii *asc);
void					*read_fbx_array(int fd, uint32_t *count,
							size_t elem_sz);
void					read_offsets(int fd, t_fbx_bin_node *node,
							bool is_64bit);
void					read_node_header(int fd, t_fbx_bin_node *node,
							bool is_64bit);
void					parse_nodes(int fd, uint64_t end_offset, bool is_64,
							t_fbx_data *d);

#endif
