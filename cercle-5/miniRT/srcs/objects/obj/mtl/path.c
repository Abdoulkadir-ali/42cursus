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
	if (load_texture_xpm(scene, &scene->materials[cur_mat].albedo_map,
			tex_path))
	{
		printf("DEBUG: Loaded texture for material %s\n",
			scene->materials[cur_mat].name);
	}
	free(tex_path);
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
	else if (mtl_is_tag(p, "map_Kd") && *cur_mat >= 0)
		mtl_handle_map_kd(scene, mtl_skip_ws(p + 6), *cur_mat, mtl_path);
}
