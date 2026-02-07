/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 21:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "objects/objects.h"
# include "objects/mesh.h"
# include "objects/fbx.h"

// Forward declaration of BVH
struct s_bvh_node;

typedef struct s_scene
{
	char			*name;
	
	// 1. Memory Pools (Contiguous Data - Hybrid Data-Oriented)
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

	t_mesh			*meshes;       // Stores both OBJ and FDF results
	int				mesh_count;
	int				mesh_cap;

	t_skinned_mesh	*animated;     // Stores FBX/GLB
	int				anim_count;
	int				anim_cap;

	t_material		*materials;
	int				mat_count;
	int				mat_cap;

	// 2. Global Resources
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	int				light_count;
	int				light_cap;


	// 3. The Accelerator (The Map)
	struct s_bvh_node	*top_level_bvh;
}				t_scene;

t_scene			*create_scene(const char *name);
void			destroy_scene(t_scene *scene);

/* Specialized Scene Adders (Direct Injection) */
int				scene_add_material(t_scene *scene, t_vec3 color);
bool			scene_add_sphere(t_scene *scene, t_sphere sphere);
bool			scene_add_plane(t_scene *scene, t_plane plane);
bool			scene_add_cylinder(t_scene *scene, t_cylinder cylinder);
bool			scene_add_cone(t_scene *scene, t_cone cone);
bool			scene_add_mesh(t_scene *scene, t_mesh mesh);
bool			scene_add_animated(t_scene *scene, t_skinned_mesh animated);
bool			scene_add_light(t_scene *scene, t_light light);

/* Global Parser Selector */
t_scene			*parse_file(const char *path);

#endif

