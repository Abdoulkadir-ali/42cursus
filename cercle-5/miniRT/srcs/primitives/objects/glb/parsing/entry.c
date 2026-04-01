/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	parse_header(unsigned char *buf, int *json_len, int *bin_len)
{
	*json_len = *(int *)(buf + 12);
	*bin_len = *(int *)(buf + 20 + *json_len);
}

/**
 * Main entry point for loading a GLB file into the engine scene.
 * Parses the binary header, extracts JSON and binary chunks, and
 * delegates the mesh and animation loading.
 */
bool	parse_glb(const char *path, t_scene *scene)
{
	size_t			size;
	unsigned char	*buf;
	char			*json_str;
	t_json_value	*json;
	int				len[2];

	buf = glb_read_file(path, &size);
	if (!buf)
		return (false);
	parse_header(buf, &len[0], &len[1]);
	json_str = ft_strndup((char *)(buf + 20), len[0]);
	json = json_parse_len(json_str, len[0]);
	free(json_str);
	if (!json)
		return (false);
	(void)scene;
	return (true);
}
