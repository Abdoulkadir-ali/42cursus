/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:58:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:33:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_H
# define GLB_H

# include "mesh.h"
# include "t_glb.h"
# include "thread.h"

# define GLB_MAGIC   0x46546C67
# define CHUNK_JSON  0x4E4F534A
# define CHUNK_BIN   0x004E4942

# define GLB_TYPE_BYTE           5120
# define GLB_TYPE_UNSIGNED_BYTE  5121
# define GLB_TYPE_SHORT          5122
# define GLB_TYPE_UNSIGNED_SHORT 5123
# define GLB_TYPE_UNSIGNED_INT   5125
# define GLB_TYPE_FLOAT          5126

# define GLB_MAX_U16             65535.0f
# define GLB_MAX_U8              255.0f

/* Prototypes - Core */
void					glb_parse_accessor(t_json_value *json, int index,
							t_accessor *acc);
void					glb_parse_buffer_view(t_json_value *json, int index,
							t_buffer_view *bv);
void					glb_extract_data(t_extract ext);
void					sample_channel(t_anim_sampler *s, float time,
							float *res, int stride);
t_mat4					make_transform(t_vec3 t, t_vec4 r_quat,
							double scale[3]);
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
void					parse_glb_material(t_glb_mat *mat);
void					load_glb_base_texture(t_json_value *json, char *bin,
							t_material *mat, t_json_value *pbr);
t_mat4					quat_to_mat4(t_vec4 q);
void					*glb_read_file(const char *path, size_t *size);

/* Prototypes - Mesh & Skeleton */
t_mat4					glb_node_transform(t_json_value *node);
t_mat4					glb_compute_world_transform(t_json_value *json,
							size_t node_idx);
void					glb_load_mesh(t_mesh *mesh, t_json_value *json,
							char *bin, size_t mesh_idx);
void					load_joints(t_json_value *json, char *bin, t_mesh *m,
							int acc_idx);
void					load_skin_weights(t_json_value *json, char *bin,
							t_mesh *m, int acc_idx);
void					glb_finalize_mesh(t_mesh *m);
t_index					*glb_load_materials(t_mesh_resource *out, void *mlx_ptr,
							t_json_value *json, char *bin);
void					glb_load_skeleton(t_mesh *mesh, t_json_value *json,
							char *bin, size_t extra_count);
int						glb_count_extra_anim_nodes(t_json_value *json);
void					glb_load_animations(t_scene *scene, t_json_value *json,
							char *bin);

/* Prototypes - Workers */
void					glb_mesh_node_search(t_glb_mesh_task *task, size_t i);
void					init_mesh_anim_defaults(t_scene *scene);
void					parse_header(unsigned char *buf, int *json_len,
							int *bin_len);
bool					parse_glb_worker(const char *path, t_scene *scene);
void					load_ibms(t_json_value *json, char *bin, int acc_idx,
							t_mat4 *dst);

/* Prototypes - Utils */
t_index					find_parent_node(t_json_value *json, size_t node_idx);
void					set_channel_path(t_anim_channel *chan, const char *p);
void					assign_anim_data(t_animation *clip, t_json_value *anim_j);
void					update_max_time(t_animation *clip, t_anim_sampler *s);
void					link_glb_bone_children(t_mesh *mesh, t_index p_idx,
							t_json_value *node, size_t *node_map);
void					link_glb_parents(t_mesh *mesh, t_json_value *joints,
							t_json_value *nodes, size_t *node_map);
void					init_bone_data(t_mesh *mesh, t_json_value *joints,
							t_json_value *nodes, size_t *node_map);
void					set_ibms(t_mesh *mesh, t_mat4 *ibms);
void					setup_skeleton(t_mesh *mesh, size_t joint_count,
							size_t extra_count);

#endif
