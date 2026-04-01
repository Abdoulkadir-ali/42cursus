/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:24:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_SCENE_H
# define TYPES_PRIMITIVES_SCENE_H

# include "t_objects.h"
# include "t_meshes.h"
# include "t_surface.h"

# define MAX_MODEL_CACHE 64

typedef struct s_cache_snap
{
	char				*name;
	t_vertex			*vertices;
	t_triangle			*triangles;
	int					*indices;
	t_vec3				*normals;
	t_vec2				*uvs;
	int					vertex_count;
	int					tri_count;
	int					mat_id;
}						t_cache_snap;

typedef struct s_model_cache
{
	char				path[512];
	t_cache_snap		*snaps;
	int					count;
}						t_model_cache;

typedef struct s_emissive_ref
{
	t_type				type;
	int					index;
}						t_emissive_ref;

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
	int							 mesh_group_count;
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

#endif
