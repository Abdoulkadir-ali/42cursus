/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 02:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "bvh.h"
#include "libft.h"

#include <stdlib.h>

// Initial capacities
static const int g_sph_init = 16;
static const int g_pln_init = 16;
static const int g_msh_init = 8;
static const int g_ani_init = 4;
static const int g_mat_init = 32;
static const int g_lgt_init = 8;
static const int g_cyl_init = 16;

static bool	init_arrays(t_scene *s)
{
	s->sphere_cap = g_sph_init;
	s->spheres = ft_calloc(s->sphere_cap, sizeof(t_sphere));
	s->plane_cap = g_pln_init;
	s->planes = ft_calloc(s->plane_cap, sizeof(t_plane));
	s->cylinder_cap = g_cyl_init;
	s->cylinders = ft_calloc(s->cylinder_cap, sizeof(t_cylinder));
	s->mesh_cap = g_msh_init;
	s->meshes = ft_calloc(s->mesh_cap, sizeof(t_mesh));
	s->anim_cap = g_ani_init;
	s->animated = ft_calloc(s->anim_cap, sizeof(t_skinned_mesh));
	s->mat_cap = g_mat_init;
	s->materials = ft_calloc(s->mat_cap, sizeof(t_material));
	s->light_cap = g_lgt_init;
	s->lights = ft_calloc(s->light_cap, sizeof(t_light));
	s->cone_cap = g_cyl_init;
	s->cones = ft_calloc(s->cone_cap, sizeof(t_cone));

	if (!s->spheres || !s->planes || !s->cylinders || !s->meshes 
		|| !s->animated || !s->materials || !s->lights || !s->cones)
		return (false);
	return (true);
}

t_scene	*create_scene(const char *name)
{
	t_scene	*s;

	s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	ft_memset(s, 0, sizeof(*s));
	s->name = name ? ft_strdup(name) : NULL;
	if (!init_arrays(s))
	{
		destroy_scene(s);
		return (NULL);
	}
	s->ambient.brightness = 0;
	s->ambient.rgb = vec3(0, 0, 0);
	scene_add_material(s, vec3(255, 0, 255));
	return (s);
}

void	destroy_mesh(t_mesh *m)
{
	if (!m) return ;
	free(m->name);
	free(m->vertices);
	free(m->normals);
	free(m->uvs);
	free(m->indices);
	if (m->internal_bvh) bvh_destroy(m->internal_bvh);
}

void	destroy_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	free(scene->name);
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	free(scene->cones);
	for (i = 0; i < scene->mesh_count; i++)
		destroy_mesh(&scene->meshes[i]);
	free(scene->meshes);
	for (i = 0; i < scene->anim_count; i++)
	{
		destroy_mesh(&scene->animated[i].base);
		free(scene->animated[i].skeleton);
		free(scene->animated[i].bone_matrices);
	}
	free(scene->animated);
	free(scene->materials);
	free(scene->lights);
	free(scene);
}
