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

#include "objects.h"

static bool	parse_cell(char *p, t_fdf_row_ctx *ctx, int col)
{
	int	w;
	int	h;

	w = ctx->dims[0];
	h = ctx->dims[1];
	if (!ft_isdigit(*p) && *p != '-' && *p != '+')
		return (false);
	ctx->mesh->vertices[ctx->row * w + col] = vec3(col - w / 2.0, ft_atoi(p)
			* 0.2, ctx->row - h / 2.0);
	return (true);
}

static t_fdf_row_ctx	init_row_ctx(t_mesh *mesh, int row, int dims[2])
{
	t_fdf_row_ctx	ctx;

	ctx.mesh = mesh;
	ctx.dims[0] = dims[0];
	ctx.dims[1] = dims[1];
	ctx.row = row;
	return (ctx);
}

static bool	parse_row_cell(char **p, t_fdf_row_ctx *ctx, int col)
{
	*p = skip_spaces(*p);
	if (!**p)
		return (false);
	if (!parse_cell(*p, ctx, col))
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
	t_fdf_row_ctx	ctx;

	p = line;
	col = 0;
	found = false;
	w = dims[0];
	ctx = init_row_ctx(mesh, row, dims);
	while (*p && col < w)
	{
		if (!parse_row_cell(&p, &ctx, col))
			break ;
		found = true;
		col++;
	}
	return (found);
}
