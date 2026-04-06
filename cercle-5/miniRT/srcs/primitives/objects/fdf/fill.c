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
#include "helpers.h"
#include "types.h"
#include "parser.h"
#include "debug.h"

bool	fdf_parse_line_row(t_parser *p, t_mesh *mesh, size_t row, t_vec2 dims);

static void	parse_rows(t_parser *p, t_mesh *mesh, t_vec2 dims)
{
	size_t	row;
	size_t	h;

	h = dims.y;
	row = 0;
	ft_print_debug("[FDF fill] parser: eof=%d bytes_read=%zu cursor=%zu\n",
		p->eof, p->bytes_read, p->cursor);
	while (parser_peek(p) != 0 && row < h)
	{
		if (fdf_parse_line_row(p, mesh, row, dims))
			row++;
		else
			ft_print_debug("[FDF fill] row %zu returned false\n", row);
	}
	ft_print_debug("[FDF fill] parsed rows: %zu / %.0f\n", row, dims.y);
}

void	fdf_fill_data(const char *path, t_mesh *mesh, t_vec2 dims)
{
	int			fd;
	t_parser	p;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	parser_init(&p, fd);
	parse_rows(&p, mesh, dims);
	close(fd);
}
