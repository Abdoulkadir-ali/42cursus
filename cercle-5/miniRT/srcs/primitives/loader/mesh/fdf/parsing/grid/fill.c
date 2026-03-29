/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses numerical values from a line into the FDF grid row.
 */
void	p_row(t_fdf *f, char *l, int y)
{
	int		x;
	char	*p;

	x = 0;
	p = l;
	while (x < f->width && *p != '\0')
	{
		while (*p != '\0' && ft_isspace(*p))
			p++;
		if (*p == '\0')
			break ;
		f->grid[y * f->width + x] = ft_atof_advance(&p);
		x++;
		while (*p != '\0' && !ft_isspace(*p) && *p != ',')
			p++;
	}
}

/**
 * @brief Populates the encompassing t_fdf grid from the parser.
 */
bool	fdf_fill_grid(t_fdf *f, t_parser *p)
{
	char		l[PARSER_BUF_SIZE + 1];
	int			y;

	y = 0;
	while (y < f->height && parser_get_line(p, l, PARSER_BUF_SIZE + 1))
	{
		p_row(f, l, y);
		y++;
	}
	return (true);
}
