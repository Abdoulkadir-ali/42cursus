/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:59:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_SCENE_H
# define PRIMITIVES_SCENE_H

# include "objects.h"
# include "dispatcher.h"
# include "parser.h"
# include "rt.h"
# include "mesh.h"
# include "surface.h"

# ifndef INIT_SCENE_CAP
#  define INIT_SCENE_CAP 128
# endif
# ifndef INIT_MESH_CAP
#  define INIT_MESH_CAP 128
# endif
# ifndef INIT_ANIM_CAP
#  define INIT_ANIM_CAP 64
# endif
# ifndef INIT_GROUP_CAP
#  define INIT_GROUP_CAP 64
# endif
# ifndef INIT_MAT_CAP
#  define INIT_MAT_CAP 256
# endif
# ifndef INIT_LIGHT_CAP
#  define INIT_LIGHT_CAP 32
# endif
# ifndef INIT_SPHERE_CAP
#  define INIT_SPHERE_CAP 128
# endif
# ifndef INIT_PLANE_CAP
#  define INIT_PLANE_CAP 128
# endif
# ifndef INIT_CYL_CAP
#  define INIT_CYL_CAP 128
# endif
# ifndef INIT_CONE_CAP
#  define INIT_CONE_CAP 128
# endif
# ifndef INIT_TRI_CAP
#  define INIT_TRI_CAP 1024
# endif
# ifndef INIT_RECT_CAP
#  define INIT_RECT_CAP 128
# endif
# ifndef INIT_PYRAMID_CAP
#  define INIT_PYRAMID_CAP 64
# endif
# ifndef INIT_BOX_CAP
#  define INIT_BOX_CAP 128
# endif
# ifndef INIT_CAPSULE_CAP
#  define INIT_CAPSULE_CAP 128
# endif

/* Lifecycle (srcs/primitives/scene/life/) */
t_scene					*create_scene(const char *name);
void					destroy_scene(t_scene *scene);
void					setup_default_scene(t_scene *scene);
bool					load_scene(t_scene *scene, const char *path);
t_scene					*parse_file(const char *path, void *mlx);

/* Internal helpers */
int						scene_material_allocate_slot(t_scene *scene);
int						scene_allocate_object_slot(void **ptr, size_t *count,
							size_t *cap, size_t sz);

#endif
