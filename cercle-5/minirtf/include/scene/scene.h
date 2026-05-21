/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:24:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:58:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "material.h"
# include "maths.h"
# include "mesh.h"
# include "shapes.h"

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	float	fov;
	float	aperture;
	float	fdist;
	float	half_w;
	float	half_h;
}			t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_vec3	color;
	int		set;
}			t_ambient;

typedef struct s_light
{
	t_vec3	pos;
	float	ratio;
	t_vec3	color;
}			t_light;

typedef struct s_blackhole
{
	t_vec3	pos;
	float	rs;
	float	lens_strength;
	float	grav_strength;
}			t_blackhole;

typedef struct s_scene
{
	t_camera	cam;
	t_camera	cam_prev;
	t_ambient	amb;
	t_light		*lights;
	size_t		n_lights;
	size_t		cap_lights;
	t_object	*bvh_objs;
	size_t		n_bvh;
	size_t		cap_bvh;
	t_object	*planes;
	size_t		n_planes;
	size_t		cap_planes;
	int			cam_set;
	t_texture	*textures;
	size_t		n_textures;
	size_t		cap_textures;
	float		cam_yaw;
	float		cam_pitch;
	t_blackhole	*bhs;
	size_t		n_bhs;
	size_t		cap_bhs;
	t_vec3		gravity;
	int			last_kind;
	int			last_first;
	int			last_count;
	int			next_group_id;
	char		group_names[64][64];
	void		*animator;
	size_t		*emit_idx;
	size_t		n_emit;
	size_t		cap_emit;
}				t_scene;

struct s_app;

/* Scene lifecycle */
int				scene_init(t_scene *s);
void			scene_free(t_scene *s);
void			scene_reset(struct s_app *app);
int				setup_default_scene(struct s_app *app);
void			autoorient_mesh(struct s_app *app);
void			autoframe_camera(struct s_app *app);

/* Object access */
t_object		*scene_obj_at(t_scene *s, int idx);
const t_object	*resolve_obj(const t_scene *s, int idx);

/* Group operations */
void			scene_group_propagate(t_scene *s, int sel);
int				scene_group_delete(t_scene *s, int sel);

/* Camera */
void			camera_setup(t_camera *c, int w, int h);
void			camera_from_yaw_pitch(t_camera *c, float yaw, float pitch);
void			camera_init_yaw_pitch(t_scene *s);
int				project_to_camera(const t_camera *c, t_vec3 p, int w, int h,
					float *sx, float *sy);

/* Scene growth */
t_light			*scene_push_light(t_scene *s);
t_object		*scene_push_plane(t_scene *s);
t_object		*scene_push_bvh(t_scene *s);

/* Save */
int				scene_save(const t_scene *s, const char *path);

#endif
