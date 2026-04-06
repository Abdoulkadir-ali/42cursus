/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_objects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_OBJECTS_H
# define TYPES_PRIMITIVES_OBJECTS_H

# include "t_maths.h"
# include "t_meshes.h"
# include "t_physics.h"

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
	TYPE_PYRAMID,
	TYPE_BOX,
	TYPE_CAPSULE,
	TYPE_MAT_MOD
}	t_type;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_EMISSIVE
}	t_light_type;

typedef struct s_sphere
{
	t_transform			transform;
	double				radius_sq;
	size_t				mat_id;
	t_vec3				temp_color;
	t_physics_body		phys;
	bool				is_deformed;
	bool				needs_uv;
	t_vec3					inv_scale;
	size_t				mat_slots[4];
	int					active_slot;
}						t_sphere;

typedef struct s_plane
{
	t_transform			transform;
	size_t				mat_id;
	t_vec3				temp_color;
	t_physics_body		phys;
	bool				needs_uv;
	size_t				mat_slots[4];
	int					active_slot;
}						t_plane;

typedef struct s_cylinder
{
	t_transform			transform;
	t_physics_body		phys;
	size_t				mat_id;
	t_vec3				temp_color;
	double				radius_sq;
	t_vec3				top;
	t_vec3				local_u;
	t_vec3				local_v;
	size_t				mat_slots[4];
	int					active_slot;
}						t_cylinder;

typedef struct s_cone
{
	t_transform			transform;
	size_t				mat_id;
	t_vec3				temp_color;
	t_physics_body		phys;
	size_t				mat_slots[4];
	int					active_slot;
}						t_cone;

typedef struct s_tri_shape
{
	t_transform			xform;
	t_physics_body		phys;
	t_vec3				v[3];
	t_vec3				normal;
	size_t				mat_id;
	t_vec3				temp_color;
	size_t				mat_slots[4];
	int					active_slot;
}						t_tri_shape;

typedef struct s_rect
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				v[4];
	t_vec3				normal;
	size_t				mat_id;
	t_vec3				temp_color;
	size_t				mat_slots[4];
	int					active_slot;
}						t_rect;

typedef struct s_pyramid
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				up;
	double				base_size;
	double				height;
	size_t				mat_id;
	t_vec3				temp_color;
	t_vec3				c[4];
	t_vec3				apex;
	size_t				mat_slots[4];
	int					active_slot;
}						t_pyramid;

typedef struct s_box
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				half_extents;
	size_t				mat_id;
	t_vec3				temp_color;
	size_t				mat_slots[4];
	int					active_slot;
}						t_box;

typedef struct s_capsule
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				axis;
	double				radius;
	double				half_height;
	size_t				mat_id;
	t_vec3				temp_color;
	size_t				mat_slots[4];
	int					active_slot;
}						t_capsule;

typedef struct s_light
{
	t_light_type		type;
	t_transform			transform;
	double				cutoff;
	double				brightness;
	t_vec3				rgb;
	size_t				id;
}						t_light;

typedef struct s_camera
{
	t_transform			transform;
	double				fov;
	size_t				id;
}						t_camera;

typedef struct s_ambient
{
	double				brightness;
	t_vec3				rgb;
}						t_ambient;

#endif
