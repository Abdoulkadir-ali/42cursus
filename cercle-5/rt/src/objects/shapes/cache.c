/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define IMPORT_CACHE_MAX 32

static char	*g_imported_files[IMPORT_CACHE_MAX];
static int	g_imported_count = 0;

int	is_file_imported(const char *path)
{
	int	i;

	i = 0;
	while (i < g_imported_count)
	{
		if (strcmp(g_imported_files[i], path) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	cache_imported_file(const char *path)
{
	if (g_imported_count < IMPORT_CACHE_MAX)
	{
		g_imported_files[g_imported_count++] = strdup(path);
	}
}
