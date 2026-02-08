/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 02:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects/fbx.h"
#include "scene.h"
#include <stdio.h>

bool	parse_fbx(const char *path, t_scene *scene)
{
	int		fd;
	char	header[30];
	ssize_t	ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	ret = read(fd, header, 23);
	close(fd);
	if (ret >= 18 && ft_strncmp(header, "Kaydara FBX Binary", 18) == 0)
	{
		printf("FBX: Detected Binary Format for %s\n", path);
		return (parse_fbx_binary(path, scene));
	}
	else
	{
		printf("FBX: Detected ASCII Format for %s\n", path);
		return (parse_fbx_ascii(path, scene));
	}
}
