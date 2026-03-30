/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void	mtl_handle_newmtl(t_mesh_resource *out, char *p, int *cur_mat)
{
	mtl_trim_line_end(p);
	*cur_mat = mesh_resource_add_material(out, p);
}

void	mtl_parse_line(t_mesh_resource *out, void *mlx_ptr, char *line,
		int *cur_mat, const char *mtl_path)
{
	char	*p;

	p = mtl_skip_ws(line);
	if (!*p || *p == '#')
		return ;
	if (mtl_is_tag(p, "newmtl"))
		mtl_handle_newmtl(out, mtl_skip_ws(p + 6), cur_mat);
	else if (*cur_mat < 0)
		return ;
	else if (mtl_is_tag(p, "map_Kd"))
		mtl_handle_map(mlx_ptr, mtl_skip_ws(p + 6),
			&out->materials[*cur_mat].albedo_map, mtl_path);
	else
		mtl_dispatch_extended(out, mlx_ptr, p, *cur_mat, mtl_path);
}

bool	parse_mtl(t_mesh_resource *out, void *mlx_ptr, const char *path)
{
	t_parser	parser;
	int			fd;
	int			cur_mat;

	printf("DEBUG: Parsing MTL file: %s\n", path);
	if (!mtl_open(path, &fd))
		return (false);
	parser_init(&parser, fd);
	cur_mat = -1;
	mtl_parse_lines(out, mlx_ptr, &parser, &cur_mat, path);
	close(fd);
	return (true);
}
