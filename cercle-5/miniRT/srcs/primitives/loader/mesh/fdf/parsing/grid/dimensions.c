/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Count numerical columns in a single FDF line.
 */
static int	get_cols(char *line)
{
	int		c;
	char	*p;

	if (line == NULL)
		return (0);
	c = 0;
	p = line;
	while (*p != '\0')
	{
		while (*p != '\0' && ft_isspace(*p))
			p++;
		if (*p == '\0')
			break ;
		if (ft_isdigit(*p) || *p == '-' || *p == '+')
			c++;
		while (*p != '\0' && !ft_isspace(*p))
			p++;
	}
	return (c);
}

/**
 * @brief Update FDF dimensions and validate consistency.
 * Static helper for dimension extraction.
 */
static bool	upd_dims(t_fdf *f, int cols)
{
	if (cols == 0)
		return (true);
	if (f->width == 0)
		f->width = cols;
	else if (f->width != cols)
		return (false);
	f->height++;
	return (true);
}

/**
 * @brief Scans the FDF file using a parser to determine grid width and height.
 * No lseek is used; relies entirely on t_parser.
 */
bool	fdf_parse_dims(t_fdf *f, t_parser *p)
{
	char		l[PARSER_BUF_SIZE + 1];
	int			cols;

	f->height = 0;
	f->width = 0;
	while (parser_get_line(p, l, PARSER_BUF_SIZE + 1))
	{
		cols = get_cols(l);
		if (upd_dims(f, cols) == false)
			return (false);
	}
	return (f->width > 0 && f->height > 0);
}
