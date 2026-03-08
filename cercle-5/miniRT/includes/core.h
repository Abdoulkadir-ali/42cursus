/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 11:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

/* std */
# include <X11/X.h>
# include <X11/keysym.h>
# include <dirent.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <zlib.h>

/* package */
# include "libft.h"
# include "mlx.h"

/* 2. MODULE TYPES & ENUMS */
# define DEBUG 0
# define GLB_MAGIC 0x46546C67
# define CHUNK_JSON 0x4E4F534A
# define CHUNK_BIN 0x004E4942
# define BVH_BINS 16

/* 2. CONSTANTS */
# define TILE_SIZE 32
# define ZOOM_SPEED 2.0
# define MOUSE_SENSITIVITY 0.005

# define EPSILON 1e-6
# define MAX_LEAF_OBJECTS 4
# define PARSER_BUF_SIZE 65536

# define INIT_SPHERE_CAP 16
# define INIT_PLANE_CAP 16
# define INIT_MESH_CAP 8
# define INIT_ANIM_CAP 4
# define INIT_GROUP_CAP 32
# define INIT_MAT_CAP 32
# define INIT_LIGHT_CAP 8
# define INIT_CYL_CAP 16
# define INIT_TRI_CAP 64
# define MAX_VALUE 1e30

/* Enums */
typedef enum e_type
{
	TYPE_NONE = 0,
	TYPE_AMBIENT,
	TYPE_CAMERA,
	TYPE_LIGHT,
	TYPE_SPHERE,
	TYPE_PLANE,
	TYPE_MESH,
	TYPE_ANIM,
	TYPE_CYLINDER,
	TYPE_CONE,
	TYPE_TRI,
	TYPE_RECT,
	TYPE_PYRAMID
}									t_type;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_EMISSIVE
}									t_light_type;

/* Forward Declarations of Structs */
typedef struct s_scene				t_scene;
typedef struct s_gui				t_gui;
typedef struct s_render_ctx			t_render_ctx;
typedef struct s_camera_controller	t_camera_controller;
typedef struct s_map				t_map;
typedef struct s_input_ctxs			t_input_ctx;
typedef struct s_bvh				t_bvh;
typedef struct s_bvh_node			t_bvh_node;
typedef struct s_vec2				t_vec2;
typedef struct s_vec3				t_vec3;
typedef struct s_mat4				t_mat4;
typedef struct s_rotator			t_rotator;
typedef struct s_transform			t_transform;
typedef struct s_aabb				t_aabb;
typedef struct s_bvh_ref			t_bvh_ref;
typedef struct s_ray				t_ray;
typedef struct s_hit				t_hit;

/* ------------------------------------------------------------------------- */
/*                           MODULE TYPEDEFS                                 */
/* ------------------------------------------------------------------------- */

typedef struct s_sphere				t_sphere;
typedef struct s_plane				t_plane;
typedef struct s_cylinder			t_cylinder;
typedef struct s_cone				t_cone;
typedef struct s_tri_shape			t_tri_shape;
typedef struct s_rect_parse			t_rect_parse;
typedef struct s_pyramid_parse		t_pyramid_parse;
typedef struct s_light				t_light;
typedef struct s_camera				t_camera;
typedef struct s_ambient			t_ambient;
typedef struct s_material			t_material;
typedef struct s_texture			t_texture;
typedef struct s_mesh				t_mesh;
typedef struct s_mesh_info			t_mesh_info;
typedef struct s_skinned_mesh		t_skinned_mesh;
typedef struct s_bone				t_bone;
typedef struct s_bone_weight		t_bone_weight;
typedef struct s_vertex				t_vertex;
typedef struct s_triangle			t_triangle;
typedef struct s_heightmap			t_heightmap;
typedef struct s_mesh_build_item	t_mesh_build_item;
typedef struct s_parser				t_parser;
typedef struct s_obj_ctx			t_obj_ctx;
typedef struct s_parse_obj			t_parse_obj;

#endif