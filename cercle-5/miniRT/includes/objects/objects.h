/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 03:22:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 17:09:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_scene	t_scene;

# include "maths.h"
# include "material.h"
# include "objects/mesh.h"
# include "objects/fbx.h"

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
}			t_type;


typedef struct s_transform
{
	t_vec3				pos;
	t_vec3				rotation;
	t_vec3				scale;
	t_vec3				forward;
	t_vec3				up;
	t_vec3				right;
}						t_transform;

typedef struct s_sphere
{
	t_vec3	pos;
	float	radius_sq;
	int		mat_id;
	t_vec3	temp_color;
}				t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	normal;
	int		mat_id;
	t_vec3	temp_color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	axis;
	float	radius;
	float	height;
	int		mat_id;
	t_vec3	temp_color;
}				t_cylinder;

typedef struct s_cone
{
	t_vec3	pos;
	t_vec3	axis;
	float	radius;
	float	height;
	int		mat_id;
	t_vec3	temp_color;
}				t_cone;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT
}				t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_vec3			pos;
	t_vec3			dir; 
	double			cutoff; // cos(angle)
	double			brightness;
	t_vec3			rgb;
}				t_light;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		rotation;
	t_vec3		forward;
	double		fov;
}				t_camera;

typedef struct s_ambient
{
	double		brightness;
	t_vec3		rgb;
}				t_ambient;

/* 
   Tagged Union Parsing Carrier. 
   Allows passing objects by value during parsing, avoiding micro-allocations.
*/
typedef struct s_parse_obj
{
	t_type	type;
	union u_data {
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
		t_mesh		mesh;
		t_light		light;
		t_camera	camera;
		t_ambient	ambient;
		t_skinned_mesh	animated;
	} data;
}			t_parse_obj;

// Prototypes
bool			parse_float_checked(const char *str, double *out);
bool			parse_vec3_checked(char *str, t_vec3 *out);
bool			parse_color_checked(char *str, t_vec3 *out);
t_parse_obj		parse_line(char *line);

// Parser per type (RT primitives)
t_parse_obj		parse_ambient(char **tokens);
t_parse_obj		parse_camera(char **tokens);
t_parse_obj		parse_light(char **tokens);
t_parse_obj		parse_spot_light(char **tokens);
t_parse_obj		parse_sphere(char **tokens);
t_parse_obj		parse_plane(char **tokens);
t_parse_obj		parse_cylinder(char **tokens);
t_parse_obj		parse_cone(char **tokens);



void			update_object_material(void *obj_data, t_type type);

#endif
