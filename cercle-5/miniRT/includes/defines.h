/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:21:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:12:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* Standard C library */
# include "libft.h"

/* STD lib */
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define EPSILON 1e-6

/* **** from includes/core.h ***** */
typedef struct s_aabb				t_aabb;
typedef struct s_ambient			t_ambient;
typedef struct s_bone				t_bone;
typedef struct s_bone_weight		t_bone_weight;
typedef struct s_box				t_box;
typedef struct s_bvh				t_bvh;
typedef struct s_bvh_node			t_bvh_node;
typedef struct s_bvh_ref			t_bvh_ref;
typedef struct s_camera				t_camera;
typedef struct s_camera_controller	t_camera_controller;
typedef struct s_capsule			t_capsule;
typedef struct s_cone				t_cone;
typedef struct s_cylinder			t_cylinder;
typedef struct s_emissive_ref		t_emissive_ref;
typedef struct s_gui				t_gui;
typedef struct s_heightmap			t_heightmap;
typedef struct s_hit				t_hit;
typedef struct s_light				t_light;
typedef struct s_map				t_map;
typedef struct s_mat4				t_mat4;
typedef struct s_material			t_material;
typedef struct s_mesh				t_mesh;
typedef struct s_mesh_build_item	t_mesh_build_item;
typedef struct s_mesh_info			t_mesh_info;
typedef struct s_parse_obj			t_parse_obj;
typedef struct s_parser				t_parser;
typedef struct s_plane				t_plane;
typedef struct s_pyramid			t_pyramid;
typedef struct s_ray				t_ray;
typedef struct s_rect				t_rect;
typedef struct s_rotator			t_rotator;
typedef struct s_scene				t_scene;
typedef struct s_skinned_mesh		t_skinned_mesh;
typedef struct s_sphere				t_sphere;
typedef struct s_texture			t_texture;
typedef struct s_transform			t_transform;
typedef struct s_tri_shape			t_tri_shape;
typedef struct s_triangle			t_triangle;
typedef struct s_vec2				t_vec2;
typedef struct s_vec3				t_vec3;
typedef struct s_vertex				t_vertex;

/* **** from includes/editor.h ***** */
typedef struct s_bool_label_arg		t_bool_label_arg;
typedef struct s_btn_rect			t_btn_rect;
typedef struct s_group_snap			t_group_snap;
typedef struct s_inspector			t_inspector;
typedef struct s_islider			t_islider;
typedef struct s_mesh_snap			t_mesh_snap;
typedef struct s_scene_panel		t_scene_panel;
typedef struct s_scene_snap			t_scene_snap;
typedef struct s_selection			t_selection;
typedef struct s_slider_arg			t_slider_arg;
typedef struct s_slider_state		t_slider_state;
typedef struct s_vec3_label_arg		t_vec3_label_arg;

/* **** from includes/gui.h ***** */
typedef struct s_crud_ui			t_crud_ui;
typedef struct s_hover_cache		t_hover_cache;
typedef struct s_key_action			t_key_action;
typedef struct s_map_entry			t_map_entry;
typedef struct s_map_job			t_map_job;
typedef struct s_panel				t_panel;
typedef struct s_render_pool		t_render_pool;
typedef struct s_render_state		t_render_state;
typedef struct s_render_thread_arg	t_render_thread_arg;
typedef struct s_tile				t_tile;
typedef struct s_widget				t_widget;
typedef struct s_window				t_window;
typedef struct s_render_pool		t_render_pool;

/* **** from includes/maths.h ***** */
typedef struct s_mat3				t_mat3;
typedef struct s_quadratic			t_quadratic;
typedef struct s_quadratic_roots	t_quadratic_roots;
typedef struct s_vec2i				t_vec2i;
typedef struct s_vec3i				t_vec3i;

/* **** from includes/objects.h ***** */

typedef struct s_accessor			t_accessor;
typedef struct s_anim_channel		t_anim_channel;
typedef struct s_anim_sampler		t_anim_sampler;
typedef struct s_animation			t_animation;
typedef struct s_bin				t_bin;
typedef struct s_bone				t_bone;
typedef struct s_bone_weight		t_bone_weight;
typedef struct s_buffer_view		t_buffer_view;
typedef struct s_bvh_sah			t_bvh_sah;
typedef struct s_bvh_split			t_bvh_split;
typedef struct s_chunk_header		t_chunk_header;
typedef struct s_fbx_array			t_fbx_array;
typedef struct s_fbx_array_req		t_fbx_array_req;
typedef struct s_fbx_bin_node		t_fbx_bin_node;
typedef struct s_fbx_buf			t_fbx_buf;
typedef struct s_fbx_build			t_fbx_build;
typedef struct s_fbx_data			t_fbx_data;
typedef struct s_fdf_dim			t_fdf_dim;
typedef struct s_glb_header			t_glb_header;
typedef struct s_hit_calc			t_hit_calc;
typedef struct s_mbvh_node			t_mbvh_node;
typedef struct s_mesh_group			t_mesh_group;
typedef struct s_mesh_init			t_mesh_init;
typedef struct s_obj_face			t_obj_face;
typedef struct s_occ_child			t_occ_child;
typedef struct s_parser				t_parser;
typedef struct s_obj_ctx			t_obj_ctx;
typedef struct s_transform_q		t_transform_q;
typedef struct s_tri_hit			t_tri_hit;
typedef struct s_tri_precomp		t_tri_precomp;

/* **** from includes/parser.h ***** */
typedef struct s_json_value			t_json_value;
typedef struct s_json_array			t_json_array;
typedef struct s_json_hash_entry	t_json_hash_entry;
typedef struct s_json_member		t_json_member;
typedef struct s_json_object		t_json_object;
typedef struct s_parser				t_parser;

/* **** from includes/physics.h ***** */
typedef struct s_collider			t_collider;
typedef struct s_body_pair			t_body_pair;
typedef struct s_contact			t_contact;
typedef struct s_dbvt				t_dbvt;
typedef struct s_dbvt_leaf			t_dbvt_leaf;
typedef struct s_dbvt_node			t_dbvt_node;
typedef struct s_edge				t_edge;
typedef struct s_epa_face			t_epa_face;
typedef struct s_epa_poly			t_epa_poly;
typedef struct s_epa_res			t_epa_res;
typedef struct s_gen_job			t_gen_job;
typedef struct s_gjk_shape			t_gjk_shape;
typedef struct s_phys_pool			t_phys_pool;
typedef struct s_physics_body		t_physics_body;
typedef struct s_shape_pair			t_shape_pair;
typedef struct s_simplex			t_simplex;
typedef struct s_static_bvh			t_static_bvh;
typedef struct s_static_node		t_static_node;
typedef struct s_sub_shape			t_sub_shape;
typedef struct s_worker_arg			t_worker_arg;
typedef struct s_phys_pool			t_phys_pool;

/* **** from includes/raytracing.h ***** */
typedef struct s_build_item			t_build_item;
typedef struct s_bvh_stack			t_bvh_stack;
typedef struct s_bvh_tmp_node		t_bvh_tmp_node;
typedef struct s_entry_point		t_entry_point;
typedef struct s_lcalc				t_lcalc;
typedef struct s_occ				t_occ;
typedef struct s_push				t_push;
typedef struct s_shading			t_shading;
typedef struct s_split_info			t_split_info;

/* **** from includes/surface.h ***** */
typedef struct s_bilinear			t_bilinear;
typedef struct s_material			t_material;
typedef struct s_scene				t_scene;
typedef struct s_texture			t_texture;

#endif /* DEFINES_H */
