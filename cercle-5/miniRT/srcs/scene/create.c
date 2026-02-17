/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:16:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "raytracing.h"

/*
** Initializes the memory pools for scene objects.
** Returns false if any allocation fails.
*/
static bool	init_arrays(t_scene *s)
{
	s->sphere_cap = INIT_SPHERE_CAP;
	s->spheres = ft_calloc(s->sphere_cap, sizeof(t_sphere));
	s->plane_cap = INIT_PLANE_CAP;
	s->planes = ft_calloc(s->plane_cap, sizeof(t_plane));
	s->cylinder_cap = INIT_CYL_CAP;
	s->cylinders = ft_calloc(s->cylinder_cap, sizeof(t_cylinder));
	s->mesh_cap = INIT_MESH_CAP;
	s->meshes = ft_calloc(s->mesh_cap, sizeof(t_mesh));
	s->anim_cap = INIT_ANIM_CAP;
	s->animated = ft_calloc(s->anim_cap, sizeof(t_skinned_mesh));
	s->mat_cap = INIT_MAT_CAP;
	s->materials = ft_calloc(s->mat_cap, sizeof(t_material));
	s->light_cap = INIT_LIGHT_CAP;
	s->lights = ft_calloc(s->light_cap, sizeof(t_light));
	s->cone_cap = INIT_CYL_CAP;
	s->cones = ft_calloc(s->cone_cap, sizeof(t_cone));
	if (!s->spheres || !s->planes || !s->cylinders || !s->meshes || !s->animated
		|| !s->materials || !s->lights || !s->cones)
		return (false);
	return (true);
}

/*
** Frees all memory associated with the scene and its objects.
*/
void	destroy_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	if (scene->bvh)
		bvh_destroy(scene->bvh);
	free(scene->name);
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	free(scene->cones);
	i = 0;
	while (i < scene->mesh_count)
		mesh_free(&scene->meshes[i++]);
	free(scene->meshes);
	i = 0;
	while (i < scene->anim_count)
	{
		mesh_free(&scene->animated[i].base);
		free(scene->animated[i].skeleton);
		free(scene->animated[i].bone_matrices);
		i++;
	}
	free(scene->animated);
	free(scene->materials);
	free(scene->lights);
	free(scene);
}

/*
** Creates a new scene with default settings and empty object lists.
*/
t_scene	*create_scene(const char *name)
{
	t_scene	*s;

	s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	ft_memset(s, 0, sizeof(*s));
	if (name)
		s->name = ft_strdup(name);
	else
		s->name = NULL;
	if (!init_arrays(s))
	{
		destroy_scene(s);
		return (NULL);
	}
	s->ambient.brightness = 0;
	s->ambient.rgb = vec3(0, 0, 0);
	scene_add_material(s, vec3(200, 160, 255));
	return (s);
}
