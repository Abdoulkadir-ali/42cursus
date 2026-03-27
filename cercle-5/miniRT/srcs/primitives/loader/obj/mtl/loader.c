/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:50:00 by abdoali          ###   ########.fr       */
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
