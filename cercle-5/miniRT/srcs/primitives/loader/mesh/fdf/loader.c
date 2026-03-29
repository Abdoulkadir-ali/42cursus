/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:39:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "debug.h"

/**
 * @brief Public file-based FDF entry point. Opens path and delegates.
 */
bool	fdf_load(t_scene *scene, const char *path)
{
	t_parser	p;
	bool		res;

	DBG_INFO_MSG(DBG_CH_PARSER, "fdf_load: '%s'\n", path);
	p.fd = open(path, O_RDONLY);
	if (p.fd < 0)
		return (false);
	p.path = path;
	res = parse_fdf(scene, &p);
	close(p.fd);
	if (!res)
		DBG_ERR_MSG(DBG_CH_PARSER, "fdf_load: FAILED '%s'\n", path);
	else
		DBG_INFO_MSG(DBG_CH_PARSER, "fdf_load: OK '%s'\n", path);
	return (res);
}

/**
 * @brief Parses a FDF file into a transient t_fdf asset (no scene touch).
 */
bool	fdf_load_to_asset(t_fdf *f, const char *path)
{
	t_parser	p;
	bool		res;

	ft_memset(f, 0, sizeof(*f));
	ft_memset(&p, 0, sizeof(p));
	f->path = path;
	p.fd = open(path, O_RDONLY);
	if (p.fd < 0)
		return (false);
	p.path = path;
	res = fdf_parse_grid_single_pass(f, &p);
	close(p.fd);
	return (res);
}
