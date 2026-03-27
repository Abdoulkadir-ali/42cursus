/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:44:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses an RT file descriptor into a scene.
 * Refactored to remove t_rt_ctx dependency.
 */
bool	parse_rt_fd(int fd, t_scene *scene)
{
	t_parser	p;

	parser_init(&p, fd);
	return (rt_parse_loop(scene, &p));
}
