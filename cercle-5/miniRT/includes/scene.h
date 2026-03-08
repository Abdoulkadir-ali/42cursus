/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 07:23:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

/* 1. EXTERNAL DEPENDENCIES */
# include "core.h"
# include "maths.h"
# include "objects.h"

/* 2. MODULE TYPES */

struct				s_scene
{
	char			*name;
	void			*mlx;
	
	t_sphere		*spheres;
	int				sphere_count;
	int				sphere_cap;
	
	t_plane			*planes;
	int				plane_count;
	int				plane_cap;

	t_cylinder		*cylinders;
	int				cylinder_count;
	int				cylinder_cap;

	t_cone			*cones;
	int				cone_count;
	int				cone_cap;

	t_tri_shape		*tris;
	int				tri_count;
	int				tri_cap;

	t_rect			*rects;
	int				rect_count;
	int				rect_cap;

	t_pyramid		*pyramids;
	int				pyramid_count;
	int				pyramid_cap;

	t_box			*boxes;
	int				box_count;
	int				box_cap;

	t_capsule		*capsules;
	int				capsule_count;
	int				capsule_cap;

	t_mesh			*meshes;
	int				mesh_count;
	int				mesh_cap;
	int				mesh_group_count;	/* next group_id to assign (legacy) */

	t_mesh_group	*groups;          /* one entry per loaded model file */
	int				group_count;
	int				group_cap;

	t_skinned_mesh	*animated;
	int				anim_count;
	int				anim_cap;

	t_material		*materials;
	int				mat_count;
	int				mat_cap;

	/* Global Resources */
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	int				light_count;
	int				light_cap;

	/* Animation Clips */
	t_animation		*clips;
	int				clip_count;
	int				clip_cap;

	/* The Accelerator */
	struct s_bvh	*bvh;
};

/* 3. FUNCTION PROTOTYPES */

/* srcs/scene/ */
t_scene				*create_scene(const char *name);
void				destroy_scene(t_scene *scene);

/* srcs/scene/add.c (Specialized Adders) */
int					scene_add_material(t_scene *scene, t_vec3 color);
int					scene_add_fresh_material(t_scene *scene, t_vec3 color);
int					scene_clone_material(t_scene *scene, int src_id);
int					scene_add_checker_material(t_scene *scene, t_vec3 a,
					t_vec3 b, double scale);
int					scene_find_material(t_scene *scene, const char *name);
int					scene_add_named_material(t_scene *scene, const char *name);

/* srcs/scene/texture_load.c */
bool				load_texture_xpm(t_scene *scene, t_texture *tex,
					const char *path);

bool				scene_add_sphere(t_scene *scene, t_sphere sphere);
bool				scene_add_plane(t_scene *scene, t_plane plane);
bool				scene_add_cylinder(t_scene *scene, t_cylinder cylinder);
bool				scene_add_cone(t_scene *scene, t_cone cone);
bool				scene_add_tri(t_scene *scene, t_tri_shape tri);
bool				scene_add_rect(t_scene *scene, t_rect rect);
bool				scene_add_pyramid(t_scene *scene, t_pyramid py);
bool				scene_add_box(t_scene *scene, t_box box);
bool				scene_add_capsule(t_scene *scene, t_capsule cap);
bool				scene_add_mesh(t_scene *scene, t_mesh mesh);
bool				scene_add_animated(t_scene *scene, t_skinned_mesh animated);
bool				scene_add_group(t_scene *scene, t_mesh_group g);
bool				scene_add_group_for_subs(t_scene *scene, const char *path,
					int start_mesh);
bool				scene_add_light(t_scene *scene, t_light light);

/* srcs/objects/rt/parsing/ (Global Selector) */
t_scene				*parse_file(const char *path, void *mlx);

#endif
