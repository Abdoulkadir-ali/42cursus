/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parser.h"

static int	count_columns(t_parser *p)
{
	int		count;
	char	c;

	count = 0;
	parser_skip_horizontal_spaces(p);
	c = parser_peek(p);
	while (c && c != '\n' && c != '\r')
	{
		if (ft_isdigit(c) || c == '-' || c == '+')
		{
			count++;
			while (parser_peek(p) && !ft_isspace(parser_peek(p)))
				parser_advance(p);
		}
		else
			parser_advance(p);
		parser_skip_horizontal_spaces(p);
		c = parser_peek(p);
	}
	if (c == '\r')
		parser_advance(p);
	if (parser_peek(p) == '\n')
		parser_advance(p);
	return (count);
}

bool	fdf_get_dimensions(const char *path, t_vec2s *dims)
{
	int			fd;
	t_parser	p;
	int			cols;
	int			line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	parser_init(&p, fd);
	dims->y = 0;
	dims->x = 0;
	line = 0;
	while (parser_peek(&p) != 0)
	{
		cols = count_columns(&p);
		line++;
		ft_print_debug("FDF: Line %d has %d columns\n", line, cols);
		if (cols > 0)
		{
			if (dims->x == 0)
				dims->x = (size_t)cols;
			else if (dims->x != (size_t)cols)
			{
				ft_print_debug("FDF: ERROR at line %d: mismatch (expected %zu, got %d)\n",
					line, dims->x, cols);
				close(fd);
				return (false);
			}
			dims->y++;
		}
	}
	close(fd);
	ft_print_debug("FDF: Final dims: %zu x %zu\n", dims->x, dims->y);
	return (dims->x > 0 && dims->y > 0);
}
