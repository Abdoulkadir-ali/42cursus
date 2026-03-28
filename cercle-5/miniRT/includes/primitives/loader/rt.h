/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:28:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:46:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LOADER_H
# define RT_LOADER_H

# include "fdf.h"
# include "fbx.h"
# include "glb.h"
# include "obj.h"

typedef struct s_rt_shape
{
	t_prim_type		type;
	t_vec3			color;
	t_prim_params	params;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
		t_box		box;
		t_capsule	capsule;
		t_pyramid	pyramid;
		t_rect		rect;
		t_vec3		tri[3];
	} data;
}					t_rt_shape;

typedef struct s_rt_buf
{
	t_rt_shape		*shapes;
	size_t			shape_count;
	size_t			shape_cap;
	t_light			*lights;
	size_t			light_count;
	size_t			light_cap;
	t_camera		camera;
	t_ambient		ambient;
	bool			has_camera;
	bool			has_ambient;
}					t_rt_buf;

bool				rt_buf_init(t_rt_buf *buf);
void				rt_buf_free(t_rt_buf *buf);
bool				rt_buf_inject(t_scene *scene, t_rt_buf *buf);
bool				rt_load(t_scene *scene, const char *path);
bool				dispatch_scan(t_scene *scene, t_rt_buf *buf, t_parser *p,
						char *id);
bool				dispatch_meshes(t_scene *scene, t_parser *p, char *id);
bool				parse_ambient(t_rt_buf *buf, t_parser *p);
bool				parse_camera(t_rt_buf *buf, t_parser *p);
bool				parse_light(t_rt_buf *buf, t_parser *p);
bool				parse_spot_light(t_rt_buf *buf, t_parser *p);
bool				parse_sphere(t_rt_buf *buf, t_parser *p);
bool				parse_plane(t_rt_buf *buf, t_parser *p);
bool				parse_cylinder(t_rt_buf *buf, t_parser *p);
bool				parse_cone(t_rt_buf *buf, t_parser *p);
bool				parse_tri_shape(t_rt_buf *buf, t_parser *p);
bool				parse_rect(t_rt_buf *buf, t_parser *p);
bool				parse_pyramid(t_rt_buf *buf, t_parser *p);
bool				parse_box(t_rt_buf *buf, t_parser *p);
bool				parse_capsule(t_rt_buf *buf, t_parser *p);

/* Scene Injection API */
bool				scene_add_primitive(t_scene *scene, t_prim_params params,
						t_prim_type type);
bool				scene_add_tri(t_scene *scene, t_vec3 v[3], int mat_id);
void				scene_apply_ambient(t_scene *scene, double brightness,
						t_vec3 rgb);
void				scene_apply_camera(t_scene *scene, t_transform transform,
						double fov);
bool				scene_add_light(t_scene *scene, t_light light);

#endif
