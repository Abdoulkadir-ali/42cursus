/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:25:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	mtl_load(const char *path, t_raw_model *model)
{
	t_parser	parser;
	int			fd;
	int			cur_mat_idx;

	if (!mtl_open(path, &fd))
		return (false);
	parser_init(&parser, fd);
	cur_mat_idx = -1;
	mtl_parse_lines_raw(model, &parser, &cur_mat_idx, path);
	close(fd);
	return (true);
}

bool	mtl_load_to_scene(const char *path, t_scene *scene)
{
	t_parser   parser;
	int        fd;
	char       line[2048];
	int        cur_mat;
	char       *p;

	if (!mtl_open(path, &fd))
		return (false);
	parser_init(&parser, fd);
	cur_mat = -1;
	while (parser_get_line(&parser, line, sizeof(line)))
	{
		p = mtl_skip_ws(line);
		if (!*p || *p == '#')
			continue;
		if (mtl_is_tag(p, "newmtl"))
		{
			p = mtl_skip_ws(p + 6);
			cur_mat = scene_add_named_material(scene, p);
			if (cur_mat < 0)
			{
				/* allocation failed; abort loading */
				close(fd);
				return (false);
			}
			continue;
		}
		if (cur_mat < 0)
			continue;
		/* dispatch property lines */
		if (mtl_is_tag(p, "Kd"))
		{
			p = mtl_skip_ws(p + 2);
			scene->materials[cur_mat].albedo_map.color_a.x = atof(p) * 255.0;
			p = ft_strchr(p, ' ');
			if (p)
			{
				p = mtl_skip_ws(p);
				scene->materials[cur_mat].albedo_map.color_a.y = atof(p) * 255.0;
				p = ft_strchr(p, ' ');
				if (p)
				{
					p = mtl_skip_ws(p);
					scene->materials[cur_mat].albedo_map.color_a.z = atof(p) * 255.0;
				}
			}
		}
		else if (mtl_is_tag(p, "Ks"))
			scene->materials[cur_mat].specular = atof(mtl_skip_ws(p + 2));
		else if (mtl_is_tag(p, "Ns"))
			scene->materials[cur_mat].shininess = atof(mtl_skip_ws(p + 2));
		else if (mtl_is_tag(p, "d"))
			scene->materials[cur_mat].transparency = 1.0 - atof(mtl_skip_ws(p + 1));
		else if (mtl_is_tag(p, "Ni"))
			scene->materials[cur_mat].refract_index = atof(mtl_skip_ws(p + 2));
		else if (mtl_is_tag(p, "Pm"))
			scene->materials[cur_mat].metallic = atof(mtl_skip_ws(p + 2));
		else if (mtl_is_tag(p, "Pr"))
			scene->materials[cur_mat].roughness = atof(mtl_skip_ws(p + 2));
		else if (mtl_is_tag(p, "map_Bump") || mtl_is_tag(p, "norm"))
		{
			char *tex = mtl_resolve_path(path, mtl_skip_ws(p + (p[0] == 'n' ? 4 : 8)));
			if (tex)
			{
				load_texture(scene, &scene->materials[cur_mat].bump_map, tex);
				free(tex);
			}
		}
		else if (mtl_is_tag(p, "map_Kd"))
		{
			char *tex = mtl_resolve_path(path, mtl_skip_ws(p + 6));
			if (tex)
			{
				load_texture(scene, &scene->materials[cur_mat].albedo_map, tex);
				free(tex);
			}
		}
	}
	close(fd);
	return (true);
}
