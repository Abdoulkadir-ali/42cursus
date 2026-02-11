/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stddef.h>

/**
 * Extracts the directory component from a file path.
 * Example: "assets/models/file.obj" -> "assets/models/"
 *          "file.obj" -> "./" (or empty string, depending on requirements.
 *          Existing code logic was ft_strrchr.
 * 
 * Logic based on existing duplication:
 * ft_strrchr(path, '/') -> if found, substr(0, ptr - path + 1).
 * Else return ft_strdup("./") or NULL? 
 * convert logic from fbx_ascii.c:
 * if (slash) dir = ft_substr(path, 0, slash - path + 1);
 * else dir = ft_strdup("./");
 */
char	*path_get_dir(const char *filepath)
{
	char	*slash;
	char	*dir;
	size_t	len;

	if (!filepath)
		return (NULL);
	slash = ft_strrchr(filepath, '/');
	if (slash)
	{
		len = slash - filepath + 1;
		dir = ft_substr(filepath, 0, len);
	}
	else
	{
		dir = ft_strdup("./");
	}
	return (dir);
}
