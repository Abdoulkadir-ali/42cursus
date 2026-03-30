/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	parse_cell(char *p, t_fdf *fdf, int col)
{
	int	w;
	int	h;

	w = fdf->dims[0];
	h = fdf->dims[1];
	if (!ft_isdigit(*p) && *p != '-' && *p != '+')
		return (false);
	fdf->mesh->vertices[fdf->row * w + col] = vec3(col - w / 2.0, ft_atoi(p)
			* 0.2, fdf->row - h / 2.0);
	return (true);
}

static t_fdf	init_row(t_mesh *mesh, int row, int dims[2])
{
	t_fdf	fdf;

	fdf.mesh = mesh;
	fdf.dims[0] = dims[0];
	fdf.dims[1] = dims[1];
	fdf.row = row;
	return (fdf);
}

static bool	parse_row_cell(char **p, t_fdf *fdf, int col)
{
	while (**p && ft_isspace(**p))
		(*p)++;
	if (!**p)
		return (false);
	if (!parse_cell(*p, fdf, col))
		return (false);
	while (**p && !ft_isspace(**p))
		(*p)++;
	return (true);
}

bool	fdf_parse_line_row(char *line, t_mesh *mesh, int row, int dims[2])
{
	char			*p;
	int				col;
	bool			found;
	int				w;
	t_fdf	fdf;

	p = line;
	col = 0;
	found = false;
	w = dims[0];
	fdf = init_row(mesh, row, dims);
	while (*p && col < w)
	{
		if (!parse_row_cell(&p, &fdf, col))
			break ;
		found = true;
		col++;
	}
	return (found);
}
