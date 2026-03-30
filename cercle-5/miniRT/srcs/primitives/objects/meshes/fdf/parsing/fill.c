/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	fdf_parse_line_row(char *line, t_mesh *mesh, int row, int dims[2]);

static void	parse_rows(t_parser *p, t_mesh *mesh, int dims[2])
{
	char	line[PARSER_BUF_SIZE + 1];
	int		row;
	int		h;

	h = dims[1];
	row = -1;
	while (parser_get_line(p, line, PARSER_BUF_SIZE + 1) && row + 1 < h)
	{
		row++;
		if (!fdf_parse_line_row(line, mesh, row, dims))
			row--;
	}
}

void	fdf_fill_data(const char *path, t_mesh *mesh, int w, int h)
{
	int			fd;
	t_parser	p;
	int			dims[2];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	parser_init(&p, fd);
	dims[0] = w;
	dims[1] = h;
	parse_rows(&p, mesh, dims);
	close(fd);
}
