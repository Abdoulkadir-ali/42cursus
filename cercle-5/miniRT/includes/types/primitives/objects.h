/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:50:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_OBJECTS_H
# define TYPES_PRIMITIVES_OBJECTS_H

# include "maths.h"
# include "types/engine/physics.h"

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
	TYPE_CAPSULE
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
	int					mat_id;
	t_vec3				temp_color;
	t_physics_body		phys;
	bool				is_deformed;
	t_mat4				inv_transform;
}						t_sphere;

typedef struct s_plane
{
	t_transform			transform;
	int					mat_id;
	t_vec3				temp_color;
	t_physics_body		phys;
}						t_plane;

typedef struct s_cylinder
{
	t_transform			transform;
	t_physics_body		phys;
	int					mat_id;
	t_vec3				temp_color;
}						t_cylinder;

typedef struct s_cone
{
	t_transform			transform;
	int					mat_id;
	t_vec3				temp_color;
	t_physics_body		phys;
}						t_cone;

typedef struct s_tri_shape
{
	t_transform			xform;
	t_physics_body		phys;
	t_vec3				v[3];
	t_vec3				normal;
	int					mat_id;
	t_vec3				temp_color;
}						t_tri_shape;

typedef struct s_rect
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				v[4];
	t_vec3				normal;
	int					mat_id;
	t_vec3				temp_color;
}						t_rect;

typedef struct s_pyramid
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				up;
	double				base_size;
	double				height;
	int					mat_id;
	t_vec3				temp_color;
	t_vec3				c[4];
	t_vec3				apex;
}						t_pyramid;

typedef struct s_box
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				half_extents;
	int					mat_id;
	t_vec3				temp_color;
}						t_box;

typedef struct s_capsule
{
	t_transform			transform;
	t_physics_body		phys;
	t_vec3				axis;
	double				radius;
	double				half_height;
	int					mat_id;
	t_vec3				temp_color;
}						t_capsule;

typedef struct s_light
{
	t_light_type		type;
	t_transform			transform;
	double				cutoff;
	double				brightness;
	t_vec3				rgb;
}						t_light;

typedef struct s_camera
{
	t_transform			transform;
	double				fov;
}						t_camera;

typedef struct s_ambient
{
	double				brightness;
	t_vec3				rgb;
}						t_ambient;

#endif
