/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:51:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

char	*resolve_fbx_path(const char *fbx_path, const char *tex_filename)
{
	char	*dir;
	char	*full_path;

	dir = path_get_dir(fbx_path);
	if (!dir)
		return (ft_strdup(tex_filename));
	full_path = ft_strjoin(dir, tex_filename);
	free(dir);
	return (full_path);
}

char	*extract_quoted(char *p, char *end)
{
	char	*start;
	char	*finish;

	while (p < end && *p && *p != '"')
		p++;
	if (p >= end || *p != '"')
		return (NULL);
	p++;
	start = p;
	while (p < end && *p && *p != '"')
		p++;
	if (p >= end || *p != '"')
		return (NULL);
	finish = p;
	return (ft_substr(start, 0, finish - start));
}

static t_index	apply_fbx_texture(t_scene *scene, char *full_path)
{
	t_index	mat_id;

	mat_id = scene_add_named_material(scene, "FBX_Mat");
	if (mat_id.error)
	{
		free(full_path);
		return (init_index(0, true));
	}
	if (load_texture_xpm(scene->mlx, &scene->materials[mat_id.i].albedo_map,
			full_path))
		ft_print_debug("FBX Texture Loaded: %s\n", full_path);
	free(full_path);
	return (mat_id);
}

t_index	parse_texture(char *p, char *end, t_scene *scene, const char *fbx_path)
{
	char	*node;
	char	*filename;
	char	*full_path;

	node = find_node(p, end, "Texture:");
	if (!node)
		return (init_index(0, true));
	node = find_node(node, end, "FileName:");
	if (!node)
		return (init_index(0, true));
	filename = extract_quoted(node, end);
	if (!filename)
		return (init_index(0, true));
	full_path = resolve_fbx_path(fbx_path, filename);
	free(filename);
	return (apply_fbx_texture(scene, full_path));
}
