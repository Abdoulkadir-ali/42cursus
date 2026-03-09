/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:26:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Expand one wildcard pattern against the current directory.
 * @param pattern Raw token text that may contain `*` or `?` wildcards.
 * @return Sorted list of matching filenames, or NULL when nothing expands.
 */
t_nodes	*expand_wildcard(char *pattern)
{
	DIR		*dir;
	t_nodes	*files;

	if (!ft_strchr(pattern, '*') && !ft_strchr(pattern, '?'))
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = collect_matches(dir, pattern);
	closedir(dir);
	if (!files)
		return (NULL);
	sort_list(&files);
	return (files);
}
