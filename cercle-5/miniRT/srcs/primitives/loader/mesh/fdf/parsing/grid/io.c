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
static bool	reset_parser(t_parser *p, const char *path)
{
	close(p->fd);
	p->fd = open(path, O_RDONLY);
	if (p->fd < 0)
		return (false);
	parser_init(p, p->fd);
	return (true);
}

/**
 * @brief Grid extraction without manual seeking.
 * First pass reads dims, reopens, second pass fills grid.
 */
bool	fdf_parse_grid_single_pass(t_fdf *f, t_parser *p)
{
	if (fdf_parse_dims(f, p) == false)
		return (false);
	if (reset_parser(p, f->path) == false)
		return (false);
	f->grid = malloc(sizeof(double) * f->width * f->height);
	if (f->grid == NULL)
		return (false);
	if (fdf_fill_grid(f, p) == false)
	{
		free(f->grid);
		f->grid = NULL;
		return (false);
	}
	return (true);
}
