/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:58:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:37:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_H
# define GLB_H

# include "mesh.h"

# define GLB_MAGIC   0x46546C67
# define CHUNK_JSON  0x4E4F534A
# define CHUNK_BIN   0x004E4942



/* Prototypes */
void					glb_parse_accessor(t_json_value *json, int index,
							t_accessor *acc);
void					glb_parse_buffer_view(t_json_value *json, int index,
							t_buffer_view *bv);
void					glb_extract_data(t_extract ext);
void					sample_channel(t_anim_sampler *s, float time,
							float *res, int stride);
t_mat4					make_transform(t_vec3 t, t_vec4 r_quat,
							double scale[3]);
void					glb_handle_indices_short(t_mesh *mesh, t_json_value *json,
							char *bin, int idx);
void					glb_load_attributes(t_mesh *mesh, t_json_value *json,
							char *bin, t_json_value *attr);
void					glb_ensure_clip_capacity(t_scene *scene, int count);
void					load_glb_sampler(t_json_value *json, char *bin,
							t_anim_sampler *s, t_json_value *sam_node);
void					glb_skin_mesh(t_mesh *mesh);
void					glb_reapply_scene_transform(t_mesh *mesh);
void					glb_update_mesh_anim(t_mesh *mesh, t_scene *scene,
							double dt);
void					vec3_mix(float *out, float *a, float *b, float t);
void					quat_slerp(float *out, float *a, float *b, float t);
void					fill_bone_trs(t_bone *bone, t_json_value *node);
void					glb_log(const char *fmt, ...);
void					parse_glb_material(t_glb_mat *mat);
void					load_glb_base_texture(t_json_value *json, char *bin,
							t_material *mat, t_json_value *pbr);
t_mat4					quat_to_mat4(t_vec4 q);
void					*glb_read_file(const char *path, size_t *size);

void					glb_load_mesh(t_mesh *mesh, t_json_value *json,
							char *bin, int mesh_idx);
t_index					*glb_load_materials(t_mesh_resource *out, void *mlx_ptr,
							t_json_value *json, char *bin);
void					glb_load_skeleton(t_mesh *mesh, t_json_value *json,
							char *bin, size_t extra_count);
int						glb_count_extra_anim_nodes(t_json_value *json);
void					glb_load_animations(t_scene *scene, t_json_value *json,
							char *bin);

/* GLB Scene Addition (srcs/primitives/scene/add/objects/mesh/loaders/) */
bool					parse_glb(const char *path, t_scene *scene);

#endif
