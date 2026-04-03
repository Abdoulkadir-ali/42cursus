/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:05:22 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:21:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	parse_glyph_row(t_parser *p, unsigned char *row)
{
	int	col;
	int	val;

	col = 0;
	while (col < 8)
	{
		val = parse_int(p);
		if (val < 0 || val > 255)
			return (false);
		row[col] = (unsigned char)val;
		col++;
	}
	return (true);
}

bool	font_load(t_gui *gui, const char *path)
{
	t_parser	p;
	int			fd;
	int			i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	parser_init(&p, fd);
	i = 0;
	while (i < 95)
	{
		if (!parse_glyph_row(&p, gui->font[i]))
		{
			close(fd);
			return (false);
		}
		i++;
	}
	close(fd);
	return (true);
}
