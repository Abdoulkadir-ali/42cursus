/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief FBX asset loader bridge for RT scene files.
 * Reuses the encompassing t_fbx container.
 */
static bool	load_fbx_asset(t_fbx *f, const char *path)
{
	f->fd = open(path, O_RDONLY);
	if (f->fd < 0)
		return (false);
	f->path = path;
	if (fbx_is_binary(f->fd))
		return (fbx_parse_binary(f));
	close(f->fd);
	return (fbx_parse_ascii(f));
}

/**
 * @brief Parses an 'fbx' entry from the scene file with spatial overrides.
 */
bool	parse_fbx_entry(t_scene *scene, t_parser *p)
{
	t_fbx		fbx;
	char		path[1024];
	t_vec3		over[4];
	double		s;
	int			i;

	if (!parser_get_next_word(p, path, 1024))
		return (false);
	ft_memset(&fbx, 0, sizeof(t_fbx));
	parse_vec3(p, &over[0]);
	parse_vec3(p, &over[1]);
	s = parse_double(p);
	parse_vec3(p, &over[2]);
	parse_vec3(p, &over[3]);
	if (!load_fbx_asset(&fbx, path))
		return (false);
	i = -1;
	while (++i < fbx.mesh_count)
	{
		fbx.meshes[i].transform.pos = vec3_add(fbx.meshes[i].transform.pos, over[0]);
		fbx.meshes[i].transform.rot = vec3_add(fbx.meshes[i].transform.rot, over[1]);
		fbx.meshes[i].transform.scale = vec3_mul_scalar(fbx.meshes[i].transform.scale, s);
		scene_add_mesh(scene, fbx.meshes[i]);
	}
	fbx_clear_asset(&fbx);
	return (true);
}
