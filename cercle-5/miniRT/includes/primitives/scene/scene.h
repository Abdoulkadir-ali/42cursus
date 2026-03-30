/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:28:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_SCENE_H
# define PRIMITIVES_SCENE_H

# include "objects.h"

typedef struct s_scene				t_scene;

/* 1. MODULE TYPES */

typedef struct s_emissive_ref
{
	t_type				type;
	int					index;
}						t_emissive_ref;

typedef struct s_cache_snap
{
	char				*name;
	t_vec3				*vertices;
	int					*indices;
	t_vec3				*normals;
	t_vec2				*uvs;
	int					vertex_count;
	int					tri_count;
	int					mat_id;
}						t_cache_snap;

# define MAX_MODEL_CACHE 64

typedef struct s_model_cache
{
	char				path[512];
	t_cache_snap		*snaps;
	int					count;
}						t_model_cache;

typedef struct s_scene
{
	char				*name;
	void				*mlx;
	
	t_sphere			*spheres;
	int					sphere_count;
	int					sphere_cap;
	
	t_plane				*planes;
	int					plane_count;
	int					plane_cap;

	t_cylinder			*cylinders;
	int					cylinder_count;
	int					cylinder_cap;

	t_cone				*cones;
	int					cone_count;
	int					cone_cap;

	t_tri_shape			*tris;
	int					tri_count;
	int					tri_cap;

	t_rect				*rects;
	int					rect_count;
	int					rect_cap;

	t_pyramid			*pyramids;
	int					pyramid_count;
	int					pyramid_cap;

	t_box				*boxes;
	int					box_count;
	int					box_cap;

	t_capsule			*capsules;
	int					capsule_count;
	int					capsule_cap;

	t_mesh				*meshes;
	int					mesh_count;
	int					mesh_cap;

	t_mesh_group		*groups;
	int					group_count;
	int					group_cap;

	t_skinned_mesh		*animated;
	int					anim_count;
	int					anim_cap;

	t_material			*materials;
	int					mat_count;
	int					mat_cap;

	t_ambient			ambient;
	t_camera			camera;
	t_light				*lights;
	int					light_count;
	int					light_cap;

	struct s_animation	*clips;
	int					clip_count;
	int					clip_cap;

	struct s_bvh		*bvh;
	t_emissive_ref		*emissive_cache;
	int					emissive_n;
	t_model_cache		cache[MAX_MODEL_CACHE];
	int					cache_count;
}						t_scene;

/* 2. FUNCTION PROTOTYPES */

/* Lifecycle (srcs/primitives/scene/life/) */
t_scene					*create_scene(const char *name);
void					destroy_scene(t_scene *scene);
void					setup_default_scene(t_scene *scene);
bool					load_scene(t_scene *scene, const char *path);
t_scene					*parse_file(const char *path, void *mlx);

/* Internal helpers */
int						scene_material_allocate_slot(t_scene *scene);
int						scene_allocate_object_slot(void **ptr, int *count,
							int *cap, size_t sz);

/* Material Addition (srcs/scene/add/material/) */
int						scene_add_material(t_scene *scene, t_vec3 color);
int						scene_add_fresh_material(t_scene *scene, t_vec3 color);
int						scene_clone_material(t_scene *scene, int src_id);
int						scene_add_checker_material(t_scene *scene, t_vec3 a,
							t_vec3 b, double scale);
int						scene_find_material(t_scene *scene, const char *name);
int						scene_add_named_material(t_scene *scene,
							const char *name);

/* RT Object Addition (srcs/scene/add/objects/rt/) */
bool					scene_add_sphere(t_scene *scene, t_sphere sphere);
bool					scene_add_plane(t_scene *scene, t_plane plane);
bool					scene_add_cylinder(t_scene *scene,
							t_cylinder cylinder);
bool					scene_add_cone(t_scene *scene, t_cone cone);
bool					scene_add_tri(t_scene *scene, t_tri_shape tri);
bool					scene_add_rect(t_scene *scene, t_rect rect);
bool					scene_add_pyramid(t_scene *scene, t_pyramid py);
bool					scene_add_box(t_scene *scene, t_box box);
bool					scene_add_capsule(t_scene *scene, t_capsule cap);
bool					scene_add_light(t_scene *scene, t_light light);

/* Mesh/Object Addition (srcs/scene/add/objects/) */
bool					scene_add_objects(t_scene *scene, const char *path);
bool					scene_add_mesh(t_scene *scene, t_mesh mesh);
bool					scene_add_collection(t_scene *scene, t_parse_obj *item,
							const char *ext);
bool					scene_add_animated(t_scene *scene,
							t_skinned_mesh animated);
bool					scene_add_group(t_scene *scene, t_mesh_group g);
bool					scene_add_group_for_subs(t_scene *scene,
							const char *path, int start_mesh);
/* Cache (srcs/scene/add/objects/mesh/cache/) */
int							find_cache_idx(t_scene *scene, const char *path);
t_model_cache				*get_cache_entry(t_scene *scene, int idx);
bool						mesh_cache_has(t_scene *scene, const char *path);
bool						mesh_cache_save(t_scene *scene, const char *path,
								int start_mesh);
bool						mesh_cache_restore(t_scene *scene, const char *path);
/* Dispatch (srcs/scene/add/objects/mesh/dispatch/) */
bool					process_primitive(t_scene *scene, t_parse_obj obj);
bool					process_system(t_scene *scene, t_parse_obj obj);
bool					process_object(t_scene *scene, t_parse_obj obj);

#endif
