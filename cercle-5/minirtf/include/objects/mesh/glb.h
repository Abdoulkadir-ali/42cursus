/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:20:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_H
# define GLB_H

# include "maths.h"
# include "skeletal.h"

# define GLB_MAGIC 0x46546C67u
# define CHUNK_JSON 0x4E4F534Au
# define CHUNK_BIN 0x004E4942u

/* glTF componentType codes */
# define GLT_BYTE 5120
# define GLT_UBYTE 5121
# define GLT_SHORT 5122
# define GLT_USHORT 5123
# define GLT_UINT 5125
# define GLT_FLOAT 5126

/* Material cache slot. */
typedef struct s_glb_mat
{
	t_vec3				color;
	t_vec3				emit;
	float				emit_pow;
	int					tex_id;
	int					emit_tex_id;
	int					unlit;
}						t_glb_mat;

/* Resolved accessor view: contiguous read with `stride` bytes per element. */
typedef struct s_glb_acc
{
	const unsigned char	*data;
	int					count;
	int					comp_type;
	int					nelems;
	int					stride;
	int					normalized;
}						t_glb_acc;

/* Loader context: shared by parser and anim files. */
typedef struct s_glb
{
	const char			*json;
	const char			*jend;
	const unsigned char	*bin;
	size_t				bin_len;
	float				rot[9];
	t_vec3				origin;
	float				scale;
	t_vec3				color;
	t_vec3				emit;
	float				emit_power;
	t_glb_mat			*mats;
	int					n_mats;
	int					*img_tex;
	int					n_imgs;
	struct s_scene		*scene;
	t_animator			*anim;
	int					bvh_base;
	int					group_id;
}						t_glb;

struct s_scene;
struct s_mesh_conf;

/* parser/load.c */
int						mesh_load_glb(struct s_scene *s, const char *path,
							struct s_mesh_conf *c);

/* parser/access.c */
int						glb_bv_get(const t_glb *g, int idx, size_t *off,
							size_t *len, int *stride);
int						glb_acc_get(const t_glb *g, int idx, t_glb_acc *out);

/* parser/read.c */
float					*glb_read_float(const t_glb *g, int acc_idx,
							int *out_count, int *out_nelems);
unsigned int			*glb_read_uint(const t_glb *g, int acc_idx,
							int *out_count, int *out_nelems);

/* parser/texture.c */
int						glb_resolve_image(t_glb *g, int img_idx);

/* parser/material.c */
void					glb_load_materials(t_glb *g);

/* parser/scene.c */
void					glb_walk_scene(t_glb *g);

/* parser/prim.c */
void					glb_capture_prim(t_glb *g, const char *prim,
							int node_idx, int skin_idx);

/* parser/xform.c */
void					glb_make_rot(float m[9], t_vec3 deg);
t_vec3					glb_apply_outer(const t_glb *g, t_vec3 p);

/* anim/node.c */
void					glb_capture_nodes(t_glb *g);

/* anim/skin.c */
void					glb_capture_skins(t_glb *g);

/* anim/clip.c */
void					glb_capture_clips(t_glb *g);

/* anim/main.c */
void					glb_animate(struct s_scene *s, float time);

#endif
