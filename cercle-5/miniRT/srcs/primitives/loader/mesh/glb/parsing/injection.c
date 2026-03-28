/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:59:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief DOD Injection of individual meshes into the scene.
 */
static void	mesh_to_scene(t_scene *s, t_glb *g, t_json_value *p, int *mmap)
{
	t_mesh	mesh;
	size_t	i;
	int		mat_idx;

	i = 0;
	while (i < p->array.count)
	{
		mat_idx = json_get_int(json_at(p, i), "material");
		init_mesh(&mesh, g->path);
		if (glb_load_primitive(&mesh, g->json, g->bin, 0, (int)i, mat_idx))
		{
			glb_load_skeleton_impl(&mesh, g->json, g->bin, 0);
			glb_compute_mesh_bbox(&mesh);
			if (mmap != NULL && mat_idx >= 0)
				mesh.mat_id = mmap[mat_idx];
			mesh.anim_base = s->clip_count - g->anim_count;
			mesh.anim_clip_count = g->anim_count;
			scene_add_mesh(s, mesh);
		}
		else
			mesh_free(&mesh);
		i++;
	}
}

/**
 * @brief High-level dispatcher for GLB asset transition to scene.
 */
void	scene_add_glb(t_scene *scene, t_glb *glb)
{
	t_json_value	*ms;
	int				*map;
	int				c;
	size_t			i;

	c = 0;
	map = glb_inject_materials(scene, glb, &c);
	i = 0;
	while (i < (size_t)glb->anim_count)
	{
		scene_add_clip(scene, glb->animations[i]);
		i++;
	}
	ms = json_get(glb->json, "meshes");
	if (ms == NULL || ms->type != JSON_ARRAY)
	{
		if (map != NULL)
			free(map);
		return ;
	}
	i = 0;
	while (i < ms->array.count)
	{
		mesh_to_scene(scene, glb, json_get(json_at(ms, i), "primitives"), map);
		i++;
	}
	if (map != NULL)
		free(map);
}

/**
 * @brief Injects GLB materials into the scene and returns an index mapping.
 */
int	*glb_inject_materials(t_scene *scene, t_glb *glb, int *count)
{
	int	*map;
	int	base;
	int	i;

	if (glb->mat_count <= 0)
		return (*count = 0, NULL);
	map = ft_calloc(glb->mat_count, sizeof(int));
	if (map == NULL)
		return (NULL);
	base = (int)scene->mat_count;
	i = 0;
	while (i < glb->mat_count)
	{
		scene_add_material(scene, &glb->materials[i]);
		map[i] = base + i;
		i++;
	}
	*count = glb->mat_count;
	return (map);
}

/**
 * @brief Internal orchestrator from file descriptor to active scene.
 */
bool	glb_parse_io(t_scene *scene, int fd, const char *path)
{
	t_glb			glb;
	char			*buf[2];
	t_json_value	*json;

	if (glb_read_buffers(fd, buf) == false)
		return (false);
	json = json_parse(buf[0]);
	if (json == NULL)
		return (false);
	ft_memset(&glb, 0, sizeof(t_glb));
	glb.json = json;
	glb.bin = buf[1];
	glb.path = path;
	glb.materials = glb_extract_materials(json, buf[1], &glb.mat_count);
	glb.animations = glb_extract_animations(json, buf[1], &glb.anim_count);
	/* load_meshes(&glb, json, buf[1]); // This would populate t_glb as asset */
	scene_add_glb(scene, &glb);
	json_free(json);
	free(buf[0]);
	free(buf[1]);
	return (true);
}
