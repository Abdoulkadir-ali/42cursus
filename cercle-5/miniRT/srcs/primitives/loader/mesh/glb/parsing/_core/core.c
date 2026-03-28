/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief DOD Mesh injection logic split to comply with function length.
 */
void	glb_inject_mesh_atomic(t_scene *s, t_glb *g, t_json_value *p, int *mmap)
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
			scene_add_mesh(s, mesh);
		}
		else
			mesh_free(&mesh);
		i++;
	}
}

/**
 * @brief Reads GLB raw buffers and extracts assets into t_glb.
 */
bool	glb_parse_to_asset(t_glb *glb, int fd, const char *path)
{
	char			*buf[2];
	t_json_value	*json;

	if (glb_read_buffers(fd, buf) == false)
		return (false);
	json = json_parse(buf[0]);
	if (json == NULL)
		return (false);
	ft_memset(glb, 0, sizeof(t_glb));
	glb->path = path;
	glb->json = json;
	glb->bin = buf[1];
	glb->materials = glb_extract_materials(json, buf[1], &glb->mat_count);
	glb->animations = glb_extract_animations(json, buf[1], &glb->anim_count);
	return (true);
}

/**
 * @brief Public GLB loader (moved from facade).
 */
bool	glb_load(t_scene *scene, const char *path)
{
	int			fd;
	t_parser	p;
	bool		res;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	p.fd = fd;
	p.path = path;
	res = parse_glb(scene, &p);
	close(fd);
	return (res);
}
