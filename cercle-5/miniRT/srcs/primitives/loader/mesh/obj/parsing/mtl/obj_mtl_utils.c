/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mtl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:38:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

void	obj_parse_mtllib_to_scene(t_obj *obj, t_parser *p, t_scene *scene,
		const char *obj_path)
{
	char    name[256];
	char    *dir;
	char    *full;
	int     i;
	size_t  base;

	if (!scene) return ;
	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	dir = path_get_dir(obj_path);
	full = ft_strdup(name);
	if (dir)
	{
		free(full);
		full = ft_strjoin(dir, name);
		free(dir);
	}
	base = scene->mat_count;
	mtl_load_to_scene(full, scene);
	if (scene->mat_count > base)
		obj->first_mtl_id = base;
	free(full);
}

void	obj_parse_usemtl_to_scene(t_obj *obj, t_parser *p, t_scene *scene)
{
	char    name[256];
	int     i;

	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	obj->current_mat_id = -1;
	if (scene)
		obj->current_mat_id = scene_find_material(scene, name);
}
