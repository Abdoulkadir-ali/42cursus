/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	mtl_open(const char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		printf("Error: Could not open MTL file %s\n", path);
		return (false);
	}
	return (true);
}

void	mtl_parse_lines_raw(t_raw_model *model, t_parser *parser, int *cur_mat_idx,
		const char *path)
{
	char	line[2048];

	while (parser_get_line(parser, line, sizeof(line)))
		mtl_parse_line_raw(model, line, cur_mat_idx, path);
}
