/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

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
	TYPE_CONE
}	t_type;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT
}	t_light_type;

/* Forward Declarations of Structs */
typedef struct s_scene				t_scene;
typedef struct s_gui				t_gui;
typedef struct s_render_ctx			t_render_ctx;
typedef struct s_camera_controller	t_camera_controller;
typedef struct s_map				t_map;
typedef struct s_input_ctxs			t_input_ctx;
typedef struct s_bvh				t_bvh;
typedef struct s_bvh_node			t_bvh_node;
typedef struct s_bvh_ref			t_bvh_ref;

typedef struct s_vec2				t_vec2;
typedef struct s_vec3				t_vec3;
typedef struct s_mat4				t_mat4;
typedef struct s_rotator			t_rotator;
typedef struct s_transform			t_transform;
typedef struct s_aabb				t_aabb;

typedef struct s_ray				t_ray;
typedef struct s_hit				t_hit;

typedef struct s_material			t_material;
typedef struct s_texture			t_texture;


/* ------------------------------------------------------------------------- */
/*                           MODULE TYPEDEFS                                 */
/* ------------------------------------------------------------------------- */

typedef struct s_sphere				t_sphere;
typedef struct s_plane				t_plane;
typedef struct s_cylinder			t_cylinder;
typedef struct s_cone				t_cone;
typedef struct s_light				t_light;
typedef struct s_camera				t_camera;
typedef struct s_ambient			t_ambient;
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
