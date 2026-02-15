/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	mtl_handle_newmtl(t_scene *scene, char *p, int *cur_mat)
{
	mtl_trim_line_end(p);
	*cur_mat = scene_add_named_material(scene, p);
}

void	mtl_handle_map_kd(t_scene *scene, char *p, int cur_mat,
		const char *mtl_path)
{
	char	*tex_path;

	mtl_trim_line_end(p);
	tex_path = mtl_resolve_path(mtl_path, p);
	if (load_texture(scene, &scene->materials[cur_mat].albedo_map,
			tex_path))
	{
		printf("DEBUG: Loaded texture for material %s\n",
			scene->materials[cur_mat].name);
	}
	free(tex_path);
}

static void	mtl_dispatch_extended(t_scene *scene, char *p, int cur_mat)
{
	double	r;
	double	g;
	double	b;

	if (mtl_is_tag(p, "Kd"))
	{
		p = mtl_skip_ws(p + 2);
		r = atof(p);
		while (*p && !ft_isspace(*p))
			p++;
		g = atof(mtl_skip_ws(p));
		while (*p && !ft_isspace(*p))
			p++;
		b = atof(mtl_skip_ws(p));
		scene->materials[cur_mat].albedo_map.color_a = vec3(r * 255,
				g * 255, b * 255);
	}
	else if (mtl_is_tag(p, "Ks"))
		scene->materials[cur_mat].specular = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "Ns"))
		scene->materials[cur_mat].shininess = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "d"))
		scene->materials[cur_mat].transparency = 1.0 - atof(mtl_skip_ws(p + 1));
}

void	mtl_parse_line(t_scene *scene, char *line, int *cur_mat,
		const char *mtl_path)
{
	char	*p;

	p = mtl_skip_ws(line);
	if (!*p || *p == '#')
		return ;
	if (mtl_is_tag(p, "newmtl"))
		mtl_handle_newmtl(scene, mtl_skip_ws(p + 6), cur_mat);
	else if (*cur_mat < 0)
		return ;
	else if (mtl_is_tag(p, "map_Kd"))
		mtl_handle_map_kd(scene, mtl_skip_ws(p + 6), *cur_mat, mtl_path);
	else
		mtl_dispatch_extended(scene, p, *cur_mat);
}
