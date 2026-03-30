/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_materials.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void	obj_parse_mtllib(t_obj *obj, t_parser *p, t_scene *scene,
		const char *obj_path)
{
	char	name[256];
	char	*dir;
	char	*full;
	int		i;

	(void)obj;
	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	dir = path_get_dir(obj_path);
	if (dir)
		full = ft_strjoin(dir, name);
	else
		full = ft_strdup(name);
	if (dir)
		free(dir);
	if (obj->first_mtl_id == -1)
		obj->first_mtl_id = scene->mat_count;
	parse_mtl(scene, full);
	free(full);
}

void	obj_parse_usemtl(t_obj *obj, t_parser *p, t_scene *scene)
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
}
