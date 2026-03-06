/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 02:57:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
