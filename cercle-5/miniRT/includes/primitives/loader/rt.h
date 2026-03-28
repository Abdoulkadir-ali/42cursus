/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:28:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:07:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LOADER_H
# define RT_LOADER_H

# include "parser.h"
# include "obj.h"
# include "glb.h"
# include "fbx.h"
# include "fdf.h"
# include "material.h"
/*
** Transient AoS structures used ONLY by the .rt loader.
** Parse the ENTIRE file into these first; inject to scene ONLY
** after full successful parsing. Never used in rendering or physics.
*/

typedef struct s_sphere
{
	t_transform	transform;
	double		radius_sq;
	int			mat_id;
	bool		is_deformed;
	t_mat4		inv_transform;
}				t_sphere;

typedef struct s_plane
{
	t_transform	transform;
	t_vec3		normal;
	int			mat_id;
}				t_plane;

typedef struct s_cylinder
{
	t_transform	transform;
	t_vec3		axis;
	double		radius_sq;
	double		height;
	int			mat_id;
}				t_cylinder;

typedef struct s_cone
{
	t_transform	transform;
	t_vec3		axis;
	double		angle;
	double		height;
	int			mat_id;
}				t_cone;

typedef struct s_box
{
	t_transform	transform;
	t_vec3		extents;
	int			mat_id;
}				t_box;

typedef struct s_capsule
{
	t_transform	transform;
	t_vec3		axis;
	double		radius;
	double		half_height;
	int			mat_id;
}				t_capsule;

typedef struct s_rect
{
	t_transform	transform;
	t_vec3		v[4];
	t_vec3		normal;
	int			mat_id;
}				t_rect;

typedef struct s_pyramid
{
	t_transform	transform;
	t_vec3		up;
	double		base_size;
	double		height;
	int			mat_id;
}				t_pyramid;

typedef struct s_tri_shape
{
	t_vec3		v[3];
	t_vec3		n;
	int			mat_id;
}				t_tri_shape;

/*
** Staging entry: one per validated shape in the parse buffer.
** mat_id is -1 until injection (color holds the raw parsed RGB).
*/
typedef struct s_rt_shape
{
	t_prim_type	type;
	t_prim_params params; /* for all non-triangle prims */
	t_vec3 v[3];          /* only for PRIM_TRIANGLE      */
	t_vec3 color;         /* raw parsed color            */
}				t_rt_shape;

/*
** Staging buffer: holds all parsed shapes, lights, camera and ambient
** for the entire .rt file before any scene mutation takes place.
*/
typedef struct s_rt_buf
{
	t_rt_shape	*shapes;
	size_t		shape_count;
	size_t		shape_cap;
	t_light		*lights;
	size_t		light_count;
	size_t		light_cap;
	t_camera	camera;
	t_ambient	ambient;
	bool		has_camera;
	bool		has_ambient;
}				t_rt_buf;

/* --- STAGING LIFECYCLE --- */
bool			rt_buf_init(t_rt_buf *buf);
void			rt_buf_free(t_rt_buf *buf);
bool			rt_buf_inject(t_scene *scene, t_rt_buf *buf);

/* --- PUBLIC API --- */
bool			rt_load(t_scene *scene, const char *path);

/* --- ENTRY POINTS (DISPATCH) --- */
bool			dispatch_scan(t_scene *scene, t_rt_buf *buf, t_parser *p,
					char *id);
bool			dispatch_meshes(t_scene *scene, t_parser *p, char *id);

/* --- ELEMENT PARSING (fill staging buf, no scene touch) --- */
bool			parse_ambient(t_rt_buf *buf, t_parser *p);
bool			parse_camera(t_rt_buf *buf, t_parser *p);
bool			parse_light(t_rt_buf *buf, t_parser *p);
bool			parse_spot_light(t_rt_buf *buf, t_parser *p);
bool			parse_sphere(t_rt_buf *buf, t_parser *p);
bool			parse_plane(t_rt_buf *buf, t_parser *p);
bool			parse_cylinder(t_rt_buf *buf, t_parser *p);
bool			parse_cone(t_rt_buf *buf, t_parser *p);
bool			parse_tri_shape(t_rt_buf *buf, t_parser *p);
bool			parse_rect(t_rt_buf *buf, t_parser *p);
bool			parse_pyramid(t_rt_buf *buf, t_parser *p);
bool			parse_box(t_rt_buf *buf, t_parser *p);
bool			parse_capsule(t_rt_buf *buf, t_parser *p);

/* --- INJECTION (called only after full parse success) --- */
void			scene_apply_ambient(t_scene *scene, double brightness,
					t_vec3 rgb);
void			scene_apply_camera(t_scene *scene, t_transform transform,
					double fov);
bool			scene_add_light(t_scene *scene, t_light light);
bool			scene_add_spot_light(t_scene *scene, t_light light);
bool			scene_add_primitive(t_scene *scene, t_prim_params params,
					t_prim_type type);
bool			scene_add_tri(t_scene *scene, t_vec3 v[3], int mat_id);
bool			scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
