/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:58:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 21:06:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_H
# define GLB_H

# include "mesh.h"
# include "../../parser/parser.h"

typedef struct s_scene	t_scene;

typedef struct s_extract
{
	char				*bin;
	t_accessor			*acc;
	t_buffer_view		*bv;
	void				*entry;
	int					stride;
	int					count;
	int					type_size;
}						t_extract;

typedef struct s_glb_header
{
	uint32_t			magic;
	uint32_t			version;
	uint32_t			length;
}						t_glb_header;

typedef struct s_chunk_header
{
	uint32_t			length;
	uint32_t			type;
}						t_chunk_header;

typedef struct s_accessor
{
	int					buffer_view;
	int					byte_offset;
	int					component_type;
	int					count;
	char				type[16];
}						t_accessor;

typedef struct s_buffer_view
{
	int					buffer;
	int					byte_offset;
	int					byte_length;
	int					byte_stride;
}						t_buffer_view;

typedef enum e_interpolation
{
	INTERP_LINEAR,
	INTERP_STEP,
	INTERP_CUBIC
}						t_interpolation;

typedef struct s_anim_sampler
{
	float				*inputs;
	float				*outputs;
	int					count;
	t_interpolation		method;
}						t_anim_sampler;

typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}						t_anim_path;

typedef struct s_anim_channel
{
	int					node_idx;
	t_anim_path			path;
	int					sampler_idx;
}						t_anim_channel;

typedef struct s_animation
{
	char				*name;
	t_anim_channel		*channels;
	int					channel_count;
	t_anim_sampler		*samplers;
	int					sampler_count;
	double				max_time;
	double				current_time;
}						t_animation;

typedef struct s_glb_mat
{
	t_mesh_resource	*out;
	void			*mlx_ptr;
	t_json_value	*json;
	char			*bin;
	int				mat_idx;
	int				*out_ids;
}	t_glb_mat;

/* Prototypes */
void					glb_parse_accessor(t_json_value *json, int index,
							t_accessor *acc);
void					glb_parse_buffer_view(t_json_value *json, int index,
							t_buffer_view *bv);
void					glb_extract_data(t_extract ext);
void					glb_handle_indices_short(t_mesh *mesh, t_json_value *json,
							char *bin, int idx);
void					glb_fill_attributes(t_mesh *mesh, t_json_value *json,
							char *bin, int ids[6]);
bool					glb_load_primitive(t_mesh *mesh, t_json_value *json,
							char *bin, int mesh_idx, int prim_idx, int mat_id);
int						*glb_load_materials(t_mesh_resource *out, void *mlx_ptr,
							t_json_value *json, char *bin);
bool					glb_read_buffers(int fd, char *buf[2]);
void					glb_load_skeleton(t_mesh *mesh, t_json_value *json,
							char *bin, int extra_count);
int						glb_count_extra_anim_nodes(t_json_value *json);
void					glb_fill_extra_anim_nodes(t_mesh *mesh,
							t_json_value *json);
void					glb_load_animations(t_mesh_resource *out,
							t_json_value *json, char *bin);
void					parse_glb_material(t_glb_mat *mat);
void					glb_skin_mesh(t_mesh *mesh);
bool					parse_glb(const char *path, t_mesh_resource *out,
							void *mlx_ptr);

#endif
