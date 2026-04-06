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
#include "parser.h"

static unsigned int	parse_hex_color(t_parser *p)
{
	unsigned int	val;
	char			c;

	val = 0;
	c = parser_peek(p);
	if (c == '0')
	{
		parser_advance(p);
		c = parser_peek(p);
		if (c == 'x' || c == 'X')
			parser_advance(p);
	}
	while (1)
	{
		c = parser_peek(p);
		if (c >= '0' && c <= '9')
			val = val * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			val = val * 16 + (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			val = val * 16 + (c - 'A' + 10);
		else
			break ;
		parser_advance(p);
	}
	return (val);
}

static void	fdf_parse_cell(t_parser *p, t_mesh *mesh, size_t row, size_t col,
		t_vec2s dims)
{
	size_t			w;
	size_t			h;
	int				val;
	char			c;
	unsigned int	*colors;

	w = dims.x;
	h = dims.y;
	val = parse_int(p);
	mesh->vertices[row * w + col].pos = vec3(col - w / 2.0,
			val * 0.2, row - h / 2.0);
	colors = (unsigned int *)mesh->extra;
	if (colors)
		colors[row * w + col] = 0xFFFFFF;
	c = parser_peek(p);
	if (c == ',')
	{
		parser_advance(p);
		if (colors)
			colors[row * w + col] = parse_hex_color(p);
		else
		{
			while (parser_peek(p) && !ft_isspace(parser_peek(p)))
				parser_advance(p);
		}
	}
}

bool	fdf_parse_line_row(t_parser *p, t_mesh *mesh, size_t row, t_vec2s dims)
{
	size_t			col;
	size_t			w;
	char			c;

	col = 0;
	w = dims.x;
	while (col < w)
	{
		parser_skip_horizontal_spaces(p);
		c = parser_peek(p);
		if (!c || c == '\n' || c == '\r')
			break ;
		fdf_parse_cell(p, mesh, row, col, dims);
		col++;
	}
	while (parser_peek(p) && parser_peek(p) != '\n' && parser_peek(p) != '\r')
		parser_advance(p);
	if (parser_peek(p) == '\r')
		parser_advance(p);
	if (parser_peek(p) == '\n')
		parser_advance(p);
	return (col > 0);
}
