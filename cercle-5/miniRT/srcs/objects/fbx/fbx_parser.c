/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Dispatches FBX parsing to binary or ASCII parser based on file header.
 *
 * @param path Path to the FBX file.
 * @param scene The scene to add the parsed mesh/animation to.
 * @return True if successful, false otherwise.
 */
bool	parse_fbx(const char *path, t_scene *scene)
{
	int		fd;
	char	header[30];
	ssize_t	ret;

	ft_print_debug("DEBUG: parse_fbx starting check for %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	ret = read(fd, header, 23);
	close(fd);
	if (ret >= 18 && ft_strncmp(header, "Kaydara FBX Binary", 18) == 0)
	{
		ft_print_debug("DEBUG: parse_fbx identified Binary format\n");
		return (parse_fbx_binary(path, scene));
	}
	ft_print_debug("DEBUG: parse_fbx defaulting to ASCII\n");
	return (parse_fbx_ascii(path, scene));
}
