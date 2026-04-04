/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:44:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_SCENE_H
# define TYPES_PRIMITIVES_SCENE_H

# include "t_objects.h"
# include "t_meshes.h"
# include "t_surface.h"
# include "thread.h"

# define MAX_MODEL_CACHE 64

typedef struct s_cache_snap
{
	char				*name;
	t_vertex			*vertices;
	t_triangle			*triangles;
	size_t				*indices;
	t_vec3				*normals;
	t_vec2				*uvs;
	size_t				vertex_count;
	size_t				tri_count;
	size_t				mat_id;
}						t_cache_snap;

typedef struct s_model_cache
{
	char				path[512];
	t_cache_snap		*snaps;
	size_t				count;
}						t_model_cache;

typedef struct s_emissive_ref
{
	t_type				type;
	size_t				index;
}						t_emissive_ref;

typedef struct s_scene
{
	char				*name;
	void				*mlx;
	
	t_sphere			*spheres;
	size_t				sphere_count;
	size_t				sphere_cap;
	
	t_plane				*planes;
	size_t				plane_count;
	size_t				plane_cap;

	t_cylinder			*cylinders;
	size_t				cylinder_count;
	size_t				cylinder_cap;

	t_cone				*cones;
	size_t				cone_count;
	size_t				cone_cap;

	t_tri_shape			*tris;
	size_t				tri_count;
	size_t				tri_cap;

	t_rect				*rects;
	size_t				rect_count;
	size_t				rect_cap;

	t_pyramid			*pyramids;
	size_t				pyramid_count;
	size_t				pyramid_cap;

	t_box				*boxes;
	size_t				box_count;
	size_t				box_cap;

	t_capsule			*capsules;
	size_t				capsule_count;
	size_t				capsule_cap;

	t_mesh				*meshes;
	size_t				mesh_count;
	size_t				mesh_cap;

	t_mesh_group		*groups;
	size_t				group_count;
	size_t				mesh_group_count;
	size_t				group_cap;

	t_skinned_mesh		*animated;
	size_t				anim_count;
	size_t				anim_cap;

	t_material			*materials;
	size_t				mat_count;
	size_t				mat_cap;

	t_ambient			ambient;
	t_camera			camera;
	t_light				*lights;
	size_t				light_count;
	size_t				light_cap;

	struct s_animation	*clips;
	size_t				clip_count;
	size_t				clip_cap;

	struct s_bvh		*bvh;
	t_emissive_ref		*emissive_cache;
	size_t				emissive_n;
	t_model_cache		cache[MAX_MODEL_CACHE];
	size_t				cache_count;
	t_thread_pool		*pool;
}						t_scene;

#endif
