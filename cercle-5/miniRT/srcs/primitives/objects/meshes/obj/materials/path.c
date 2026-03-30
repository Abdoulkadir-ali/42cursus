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

#include "obj.h"

void	mtl_handle_map(t_scene *scene, char *p, t_texture *tex,
		const char *mtl_path)
{
	char	*tex_path;

	mtl_trim_line_end(p);
	tex_path = mtl_resolve_path(mtl_path, p);
	load_texture(scene, tex, tex_path);
	free(tex_path);
}

static void	mtl_dispatch_maps(t_scene *scene, char *p, int cur_mat,
		const char *mtl_path)
{
	int	offset;

	if (mtl_is_tag(p, "map_Bump") || mtl_is_tag(p, "norm"))
	{
		offset = 8;
		if (p[0] == 'n')
			offset = 4;
		mtl_handle_map(scene, mtl_skip_ws(p + offset),
			&scene->materials[cur_mat].bump_map, mtl_path);
	}
	else if (mtl_is_tag(p, "map_Pm"))
		mtl_handle_map(scene, mtl_skip_ws(p + 6),
			&scene->materials[cur_mat].metallic_map, mtl_path);
	else if (mtl_is_tag(p, "map_Pr"))
		mtl_handle_map(scene, mtl_skip_ws(p + 6),
			&scene->materials[cur_mat].roughness_map, mtl_path);
}

static void	mtl_parse_albedo(t_scene *scene, char *p, int i)
{
	p = mtl_skip_ws(p + 2);
	scene->materials[i].albedo_map.color_a.x = atof(p) * 255;
	p = ft_strchr(p, ' ');
	if (p)
	{
		p = mtl_skip_ws(p);
		scene->materials[i].albedo_map.color_a.y = atof(p) * 255;
		p = ft_strchr(p, ' ');
		if (p)
			scene->materials[i].albedo_map.color_a.z = atof(p) * 255;
	}
}

void	mtl_dispatch_extended(t_scene *scene, char *p, int cur_mat,
		const char *mtl_path)
{
	if (mtl_is_tag(p, "Kd"))
		mtl_parse_albedo(scene, p, cur_mat);
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
	else
		mtl_dispatch_maps(scene, p, cur_mat, mtl_path);
}
