/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:04:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 12:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	fbx_load(const char *path, t_raw_model *out)
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
		return (fbx_load_binary(path, out));
	return (fbx_load_ascii(path, out));
}
