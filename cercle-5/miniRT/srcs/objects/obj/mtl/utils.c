/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

char	*mtl_resolve_path(const char *mtl_path, const char *tex_filename)
{
	char	*dir;
	char	*full_path;

	dir = path_get_dir(mtl_path);
	if (!dir)
		return (ft_strdup(tex_filename));
	full_path = ft_strjoin(dir, tex_filename);
	free(dir);
	return (full_path);
}

void	mtl_trim_line_end(char *p)
{
	char	*end;

	end = p;
	while (*end && *end != '\n' && *end != '\r')
		end++;
	*end = 0;
}

char	*mtl_skip_ws(char *p)
{
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	return (p);
}

bool	mtl_is_tag(char *p, const char *tag)
{
	int	len;

	len = (int)ft_strlen(tag);
	if (ft_strncmp(p, tag, len) != 0)
		return (false);
	return (p[len] == ' ' || p[len] == '\t');
}
