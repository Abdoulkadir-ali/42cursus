/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:16:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Public file-based FDF entry point. Opens path and delegates.
 */
bool	fdf_load(t_scene *scene, const char *path)
{
	t_parser	p;
	bool		res;

	p.fd = open(path, O_RDONLY);
	if (p.fd < 0)
		return (false);
	p.path = path;
	res = parse_fdf(scene, &p);
	close(p.fd);
	return (res);
}
