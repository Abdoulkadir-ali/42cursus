/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_raw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:38:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses individual meshes and populates the GLB asset container.
 */
void	glb_load_meshes_from_json(t_glb *glb, t_json_value *json, char *bin)
{
	t_json_value	*meshes;
	size_t			i;
	int				mat;

	meshes = json_get(json, "meshes");
	if (meshes == NULL || meshes->type != JSON_ARRAY)
		return ;
	glb->mesh_count = (int)meshes->array.count;
	glb->meshes = ft_calloc(glb->mesh_count, sizeof(t_mesh_asset));
	glb->mesh_mats = ft_calloc(glb->mesh_count, sizeof(int));
	i = 0;
	while (i < (size_t)glb->mesh_count)
	{
		mat = json_get_int(json_at(json_get(json_at(meshes, i),
						"primitives"), 0), "material");
		init_mesh(&glb->meshes[i], glb->path);
		if (glb_load_primitive(&glb->meshes[i], json, bin, (int)i, 0, mat))
		{
			glb_load_skeleton_impl(&glb->meshes[i], json, bin, 0);
			glb_compute_mesh_bbox(&glb->meshes[i]);
			glb->mesh_mats[i] = mat;
		}
		i++;
	}
}

/**
 * @brief Core loader for a standalone GLB asset container.
 */
t_glb	*glb_load_asset(const char *path)
{
	t_glb	*glb;
	char	*buf[2];
	t_json_value	*json;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0 || glb_read_buffers(fd, buf) == false)
		return (NULL);
	close(fd);
	json = json_parse(buf[0]);
	if (json == NULL)
		return (NULL);
	glb = ft_calloc(1, sizeof(t_glb));
	glb->path = path;
	glb->materials = glb_extract_materials(json, buf[1], &glb->mat_count);
	glb->animations = glb_extract_animations(json, buf[1], &glb->anim_count);
	glb_load_meshes_from_json(glb, json, buf[1]);
	json_free(json);
	free(buf[0]);
	free(buf[1]);
	return (glb);
}
