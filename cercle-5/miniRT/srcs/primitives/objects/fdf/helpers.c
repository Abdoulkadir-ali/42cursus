/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:18:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parser.h"

static unsigned int	parse_hex_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

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
	while (ft_ishex(parser_peek(p)))
	{
		val = val * 16 + parse_hex_digit(parser_peek(p));
		parser_advance(p);
	}
	return (val);
}

static void	set_cell_color(t_parser *p, unsigned int *colors, size_t idx)
{
	if (parser_peek(p) == ',')
	{
		parser_advance(p);
		if (colors)
			colors[idx] = parse_hex_color(p);
		else
		{
			while (parser_peek(p) && !ft_isspace(parser_peek(p)))
				parser_advance(p);
		}
	}
}

static void	fdf_parse_cell(t_parser *p, t_mesh *mesh, t_vec2s pos, t_vec2s dims)
{
	int				val;
	unsigned int	*colors;
	size_t			idx;

	val = parse_int(p);
	mesh->vertices[pos.y * dims.x + pos.x].pos = vec3(pos.x - dims.x / 2.0,
			val * 0.2, pos.y - dims.y / 2.0);
	colors = (unsigned int *)mesh->extra;
	idx = pos.y * dims.x + pos.x;
	if (colors)
		colors[idx] = 0xFFFFFF;
	set_cell_color(p, colors, idx);
}

bool	fdf_parse_line_row(t_parser *p, t_mesh *mesh, size_t row, t_vec2s dims)
{
	size_t			col;

	col = 0;
	while (col < dims.x)
	{
		parser_skip_horizontal_spaces(p);
		if (!parser_peek(p) || parser_peek(p) == '\n' || parser_peek(p) == '\r')
			break ;
		fdf_parse_cell(p, mesh, (t_vec2s){col, row}, dims);
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
