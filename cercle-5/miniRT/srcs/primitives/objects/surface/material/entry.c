/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:02:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:47:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "obj.h"

bool	parse_mtl(t_scene *scene, t_obj *obj, const char *path)
{
	(void)scene;
	(void)obj;
	(void)path;
	ft_print_debug("WARNING: MTL parsing not implemented yet: %s\n", path);
	return (true);
}

static char	*get_mtl_full_path(const char *name, const char *obj_path)
{
	char	*dir;
	char	*full;

	dir = path_get_dir(obj_path);
	if (dir)
		full = ft_strjoin(dir, name);
	else
		full = ft_strdup(name);
	if (dir)
		free(dir);
	return (full);
}

/**
 * Orchestrates OBJ material library loading.
 * Relocated to the scene domain as it bridge the parsed object context
 * with the global scene material store.
 */
bool	obj_parse_mtllib(t_scene *scene, t_obj *obj, t_parser *p,
			const char *obj_path)
{
	char	name[256];
	char	*full;
	int		i;

	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	full = get_mtl_full_path(name, obj_path);
	if (obj->first_mtl_id.error)
		obj->first_mtl_id = init_index(scene->mat_count, false);
	parse_mtl(scene, NULL, full);
	free(full);
	return (true);
}

/**
 * Orchestrates the 'usemtl' directive by searching the scene state.
 */
bool	obj_parse_usemtl(t_scene *scene, t_obj *obj, t_parser *p)
{
	char	name[256];
	int		i;

	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	obj->current_mat_id = scene_find_material(scene, name);
	return (true);
}
