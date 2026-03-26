/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:26:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

/* External dependencies */
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* 1. EXTERNAL DEPENDENCIES */
# include "defines.h"
# include "maths.h"
# include "objects.h"
# include "physics.h"

# define INIT_SPHERE_CAP 16
# define INIT_PLANE_CAP 16
# define INIT_MESH_CAP 8
# define INIT_ANIM_CAP 4
# define INIT_GROUP_CAP 32
# define INIT_MAT_CAP 32
# define INIT_LIGHT_CAP 8
# define INIT_CYL_CAP 16
# define INIT_TRI_CAP 64
# define INIT_RECT_CAP 32
# define INIT_PYRAMID_CAP 32
# define INIT_BOX_CAP 32
# define INIT_CAPSULE_CAP 32
# define MAX_VALUE 1e30

# define SCALE_EPSILON 1e-6
# define HALF_SCALE 0.5

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
	int				mesh_group_count;
	t_mesh_group	*groups;
	int				group_count;
	int				group_cap;

	t_skinned_mesh	*animated;
	int				anim_count;
	int				anim_cap;

	t_material		*materials;
	int				mat_count;
	int				mat_cap;
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	int				light_count;
	int				light_cap;
	t_animation		*clips;
	int				clip_count;
	int				clip_cap;
	struct s_bvh	*bvh;
	t_emissive_ref	*emissive_cache;
	int				emissive_n;

	/* Physics Context (Stage 9 - No Globals) */
	t_dbvt			dbvt;
	t_phys_pool		pool;
	t_static_bvh	*static_bvh;
};

/* dynarray helper moved from utils */
bool				dynarray_ensure(void **array, size_t count, size_t *cap,
						size_t elem_size);

/* Helper for int-based counts (implemented in srcs/scene/dynarray_helper.c) */
bool				DYNARRAY_ENSURE_INT(void **arr, int *count_ptr,
						int *cap_ptr, size_t elem_size);

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
bool				load_texture(t_scene *scene, t_texture *tex,
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
bool				scene_apply_compound(t_scene *scene,
						struct s_json_value *shape_obj);

/* srcs/objects/rt/parsing/ (Global Selector) */
t_scene				*parse_file(const char *path, void *mlx);

#endif
