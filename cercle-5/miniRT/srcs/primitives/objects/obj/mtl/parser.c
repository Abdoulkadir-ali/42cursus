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

#include "objects.h"

bool	parse_mtl(t_scene *scene, const char *path)
{
	t_parser	parser;
	int			fd;
	int			cur_mat;

	printf("DEBUG: Parsing MTL file: %s\n", path);
	if (!mtl_open(path, &fd))
		return (false);
	parser_init(&parser, fd);
	cur_mat = -1;
	mtl_parse_lines(scene, &parser, &cur_mat, path);
	close(fd);
	return (true);
}
