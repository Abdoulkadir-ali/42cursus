/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

void	mtl_handle_newmtl_raw(t_raw_model *model, char *p, int *cur_mat_idx)
{
	mtl_trim_line_end(p);
	if (dynarray_ensure((void **)&model->materials, model->mat_count + 1,
			NULL, sizeof(t_raw_material)))
	{
		*cur_mat_idx = model->mat_count++;
		ft_memset(&model->materials[*cur_mat_idx], 0, sizeof(t_raw_material));
		ft_strlcpy(model->materials[*cur_mat_idx].name, p, 64);
	}
}

static void	mtl_handle_map_raw(t_raw_material *mat, char *p, const char *mtl_path)
{
	char	*tex_path;

	mtl_trim_line_end(p);
	tex_path = mtl_resolve_path(mtl_path, p);
	if (tex_path)
	{
		ft_strlcpy(mat->albedo_map_path, tex_path, 256);
		mat->has_tex = true;
		free(tex_path);
	}
}

void	mtl_dispatch_extended_raw(t_raw_material *mat, char *p, const char *mtl_path)
{
	if (mtl_is_tag(p, "Kd"))
	{
		p = mtl_skip_ws(p + 2);
		mat->color.x = atof(p) * 255;
		p = ft_strchr(p, ' ');
		if (p)
		{
			p = mtl_skip_ws(p);
			mat->color.y = atof(p) * 255;
			p = ft_strchr(p, ' ');
			if (p)
				mat->color.z = atof(p) * 255;
		}
	}
	else if (mtl_is_tag(p, "Ks"))
		mat->specular = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "Ns"))
		mat->shininess = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "d"))
		mat->transparency = 1.0 - atof(mtl_skip_ws(p + 1));
	else if (mtl_is_tag(p, "Ni"))
		mat->refract_index = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "Pm"))
		mat->metallic = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "Pr"))
		mat->roughness = atof(mtl_skip_ws(p + 2));
	else if (mtl_is_tag(p, "map_Bump") || mtl_is_tag(p, "norm"))
		mtl_handle_map_raw(mat, mtl_skip_ws(p + (p[0] == 'n' ? 4 : 8)), mtl_path);
	else if (mtl_is_tag(p, "map_Kd"))
		mtl_handle_map_raw(mat, mtl_skip_ws(p + 6), mtl_path);
}

void	mtl_parse_line_raw(t_raw_model *model, char *line, int *cur_mat_idx,
		const char *mtl_path)
{
	char	*p;

	p = mtl_skip_ws(line);
	if (!*p || *p == '#')
		return ;
	if (mtl_is_tag(p, "newmtl"))
		mtl_handle_newmtl_raw(model, mtl_skip_ws(p + 6), cur_mat_idx);
	else if (*cur_mat_idx < 0)
		return ;
	else
		mtl_dispatch_extended_raw(&model->materials[*cur_mat_idx], p, mtl_path);
}
