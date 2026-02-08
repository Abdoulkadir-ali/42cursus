/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 03:22:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 13:13:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_scene		t_scene;
typedef struct s_parse_obj	t_parse_obj;
typedef struct s_mesh		t_mesh;

#include "libft.h"
# include "material.h"
# include "maths.h"
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
}							t_type;

typedef struct s_sphere
{
	t_transform				transform;
	float					radius_sq;
	int						mat_id;
	t_vec3					temp_color;
}							t_sphere;

typedef struct s_plane
{
	t_transform				transform;
	int						mat_id;
	t_vec3					temp_color;
}							t_plane;

typedef struct s_cylinder
{
	t_transform				transform;
	int						mat_id;
	t_vec3					temp_color;
}							t_cylinder;

typedef struct s_cone
{
	t_transform				transform;
	int						mat_id;
	t_vec3					temp_color;
}							t_cone;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT
}							t_light_type;

typedef struct s_light
{
	t_light_type			type;
	t_transform				transform;
	double cutoff; // cos(angle)
	double					brightness;
	t_vec3					rgb;
}							t_light;

typedef struct s_camera
{
	t_transform				transform;
	double					fov;
}							t_camera;

typedef struct s_ambient
{
	double					brightness;
	t_vec3					rgb;
}							t_ambient;

typedef struct s_mesh_info
{
	char					*path;
	t_transform				transform;
}							t_mesh_info;

/*
   Tagged Union Parsing Carrier.
   Allows passing objects by value during parsing, avoiding micro-allocations.
*/
typedef struct s_parse_obj
{
	t_type type;
	union					u_data
	{
		t_sphere			sphere;
		t_plane				plane;
		t_cylinder			cylinder;
		t_cone				cone;
		t_mesh				mesh;
		t_light				light;
		t_camera			camera;
		t_ambient			ambient;
		t_skinned_mesh		animated;
		t_mesh_info			mesh_info;
	} data;
}							t_parse_obj;

// Prototypes
bool						parse_float_checked(const char *str, double *out);
bool						parse_vec3_checked(char *str, t_vec3 *out);
bool						parse_color_checked(char *str, t_vec3 *out);
t_parse_obj					parse_line(char *line);

// Parser per type (RT primitives)
t_parse_obj					parse_ambient(char **tokens);
t_parse_obj					parse_camera(char **tokens);
t_parse_obj					parse_light(char **tokens);
t_parse_obj					parse_spot_light(char **tokens);
t_parse_obj					parse_sphere(char **tokens);
t_parse_obj					parse_plane(char **tokens);
t_parse_obj					parse_cylinder(char **tokens);
t_parse_obj					parse_cone(char **tokens);
t_parse_obj					parse_mesh_entry(char **tokens, t_type type);

void						update_object_material(void *obj_data, t_type type);

#endif
