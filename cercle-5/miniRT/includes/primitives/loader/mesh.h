/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:11:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_LOADER_H
# define MESH_LOADER_H

# include "scene.h"

/* ----------------------------------------------------------------- */
/*  t_mesh — LOADER TRANSIENT ONLY                                   */
/*  Built by loaders (GLB/FBX/OBJ/FDF), flattened into scene        */
/*  via scene_add_mesh(), then freed. Never touches the engine.      */
/* ----------------------------------------------------------------- */

typedef struct s_mesh_init
{
	int		v_count;
	int		i_count;
	bool	has_normals;
	bool	has_uvs;
}	t_mesh_init;


typedef struct s_mesh
{
	t_vec3			*vertices;
	size_t			vertex_count;
	int				*indices;
	size_t			tri_count;
	t_vec2			*uvs;
	t_vec3			*normals;
	int				mat_id;
	t_transform		transform;
	char			*name;
	t_aabb			bbox;
	int				group_id;
	uint16_t		*bone_ids;
	float			*weights;
	int				*weight_counts;
	int				*weight_offsets;
	t_bone			*skeleton;
	t_mat4			*bone_matrices;
	int				bone_count;
	int				anim_base;
	int				anim_clip_count;
}	t_mesh;

/* ----------------------------------------------------------------- */
/*  INJECTION — flattens transient into scene, then frees t_mesh     */
/* ----------------------------------------------------------------- */

bool	scene_add_mesh(t_scene *scene, t_mesh mesh);
bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated);
bool	scene_add_clip(t_scene *scene, t_animation anim);

/* ----------------------------------------------------------------- */
/*  LIFECYCLE — used only inside srcs/primitives/loader/             */
/* ----------------------------------------------------------------- */

void	init_mesh(t_mesh *mesh, const char *name);
void	mesh_free(t_mesh *mesh);
bool	mesh_load_from_file(t_mesh *mesh, const char *path);
bool	load_mesh_file(t_scene *scene, const char *path);
bool	load_injected_mesh(t_scene *scene, const char *path,
			t_transform transform, t_vec3 color, t_vec3 emission);

#endif
