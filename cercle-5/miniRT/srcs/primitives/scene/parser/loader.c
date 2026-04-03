/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_rt_fd(int fd, t_scene *scene)
{
	t_rt		rt;
	t_parser	parser;

	ft_memset(&rt, 0, sizeof(rt));
	ft_memset(&parser, 0, sizeof(parser));
	rt.parser = &parser;
	rt.status = true;
	rt.fd = fd;
	parser_init(rt.parser, fd);
	rt_parse_loop(scene, &rt);
	return (rt.status);
}

bool	parse_rt(const char *path, t_scene *scene)
{
	t_rt		rt;
	t_parser	parser;

	ft_memset(&rt, 0, sizeof(rt));
	ft_memset(&parser, 0, sizeof(parser));
	rt.parser = &parser;
	if (!rt_init_parser(&rt, path))
		return (false);
	rt_parse_loop(scene, &rt);
	close(rt.fd);
	return (rt.status);
}
