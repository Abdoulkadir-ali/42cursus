/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:16:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Resets the parser by reopening the file.
 * Avoids manual lseek by leveraging OS file pointer resets.
 */
/**
 * @brief Performs a high-performance single-pass FDF extraction.
 * Dynamically grows the grid as lines are parsed to eliminate redundant I/O.
 */
bool	fdf_parse_grid_single_pass(t_fdf *f, t_parser *p)
{
	char	l[PARSER_BUF_SIZE + 1];
	int		cap;
	int		y;
	int		cols;
	double	*tmp;

	cap = 0;
	y = 0;
	while (parser_get_line(p, l, PARSER_BUF_SIZE + 1))
	{
		cols = get_cols(l);
		if (cols == 0)
			continue ;
		if (f->width == 0)
			f->width = cols;
		else if (f->width != cols)
			return (false);
		if (y >= cap)
		{
			cap = (cap == 0) ? 64 : cap * 2;
			tmp = realloc(f->grid, (size_t)cap * f->width * sizeof(double));
			if (!tmp)
				return (false);
			f->grid = tmp;
		}
		p_row(f, l, y++);
	}
	f->height = y;
	return (f->width > 0 && f->height > 0);
}
