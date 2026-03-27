#include "../constants.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

# include "objects.h"



typedef struct s_scene
{
	char							*name;
	void							*mlx;

	t_sphere						*spheres;
	int								sphere_count;
	int								sphere_cap;

	t_plane							*planes;
	int								plane_count;
	int								plane_cap;

	t_cylinder						*cylinders;
	int								cylinder_count;
	int								cylinder_cap;

	t_cone							*cones;
	int								cone_count;
	int								cone_cap;

	t_tri_shape						*tris;
	int								tri_count;
	int								tri_cap;

	t_rect							*rects;
	int								rect_count;
	int								rect_cap;

	t_pyramid						*pyramids;
	int								pyramid_count;
	int								pyramid_cap;

	t_box							*boxes;
	int								box_count;
	int								box_cap;

	t_capsule						*capsules;
	int								capsule_count;
	int								capsule_cap;

	t_mesh							*meshes;
	int								mesh_count;
	int								mesh_cap;
	t_mesh_group					*groups;
	int								group_count;
	int								group_cap;

	t_skinned_mesh					*animated;
	int								anim_count;
	int								anim_cap;

	t_material						*materials;
	int								mat_count;
	int								mat_cap;
	t_ambient						ambient;
	t_camera						camera;
	t_light							*lights;
	int								light_count;
	int								light_cap;

	t_animation						*clips;
	int								clip_count;
	int								clip_cap;
	struct s_bvh					*bvh;
	t_emissive_ref					*emissive_cache;
	int								emissive_n;
	bool							simulate_physics;
	uint32_t						version;
}	t_scene;

/* ------------------------------------------------------------------------- */
/*                             SCENE MANAGEMENT                              */
/* ------------------------------------------------------------------------- */

t_scene		*create_scene(const char *name);
void		destroy_scene(t_scene *scene);

/* Material logic moved to surface.h - use includes/primitives/surface.h */

bool		scene_add_ambient(t_scene *scene, double brightness, t_vec3 rgb);
bool		scene_add_camera(t_scene *scene, t_camera camera);
bool		scene_add_light(t_scene *scene, t_light light);
bool		scene_add_sphere(t_scene *scene, t_sphere sphere);
bool		scene_add_plane(t_scene *scene, t_plane plane);
bool		scene_add_cylinder(t_scene *scene, t_cylinder cylinder);
bool		scene_add_cone(t_scene *scene, t_cone cone);
bool		scene_add_tri(t_scene *scene, t_tri_shape tri);
bool		scene_add_rect(t_scene *scene, t_rect rect);
bool		scene_add_pyramid(t_scene *scene, t_pyramid pyramid);
bool		scene_add_box(t_scene *scene, t_box box);
bool		scene_add_capsule(t_scene *scene, t_capsule capsule);

/* Bridge Parsers (Rule 2) */
bool		parse_ambient(t_scene *scene, struct s_parser *p);
bool		parse_camera(t_scene *scene, struct s_parser *p);
bool		parse_light(t_scene *scene, struct s_parser *p);
bool		parse_spot_light(t_scene *scene, struct s_parser *p);
bool		parse_sphere(t_scene *scene, struct s_parser *p);
bool		parse_plane(t_scene *scene, struct s_parser *p);
bool		parse_cylinder(t_scene *scene, struct s_parser *p);
bool		parse_cone(t_scene *scene, struct s_parser *p);
bool		parse_tri_shape(t_scene *scene, struct s_parser *p);
bool		parse_rect(t_scene *scene, struct s_parser *p);
bool		parse_pyramid(t_scene *scene, struct s_parser *p);
bool		parse_box(t_scene *scene, struct s_parser *p);
bool		parse_capsule(t_scene *scene, struct s_parser *p);
bool		parse_mesh_entry(t_scene *scene, struct s_parser *p, t_type type);
bool		scene_add_mesh(t_scene *scene, t_mesh mesh);
bool		scene_add_light(t_scene *scene, t_light light);
bool		scene_add_animation(t_scene *scene, t_animation anim);
bool		scene_add_raw_model(t_scene *scene, t_raw_model model);
bool		scene_add_group(t_scene *scene, t_mesh_group g);
bool		scene_add_group_for_subs(t_scene *scene, const char *path, int start_mesh);

/* ------------------------------------------------------------------------- */
/*                               RT PARSER                                   */
/* ------------------------------------------------------------------------- */

t_scene		*parse_file(const char *path, void *mlx);
bool		scene_parse_rt(t_scene *scene, const char *path);
bool		parse_rt_fd(int fd, t_scene *scene);
bool		rt_parse_loop(t_scene *scene, struct s_parser *p);

/* The Dispatcher now only adds Prepared Objects from the Object Layer */
bool		dispatch_scan(t_scene *scene, struct s_parser *p, char *id);
bool		rt_parse_token(struct s_parser *p, char *buf, size_t max_len);

/* Mesh Cache & Injection logic (RT specific) */
bool		handle_mesh_injection(t_scene *scene, struct s_parser *p, t_type type);
bool		handle_mesh_injection_internal(t_scene *scene, t_mesh_info *info, t_type type);
void		rt_parse_scale_raw(struct s_parser *p, t_vec3 *scale);
bool		mesh_cache_restore(const char *path, t_scene *scene);
bool		mesh_cache_has(const char *path);
bool		mesh_cache_save(const char *path, t_scene *scene, int start_mesh);
bool		load_injected_mesh(const char *path, t_raw_model *model, t_transform transform, t_vec3 color, t_vec3 emission);

#endif
