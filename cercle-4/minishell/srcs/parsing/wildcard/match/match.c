/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:31:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_nodes	*process_directory(DIR *dir, char *pat_copy, int require_dir)
{
	t_nodes			*files;
	int				match_count;
	int				entry_count;
	struct dirent	*entry;

	files = NULL;
	match_count = 0;
	entry_count = 0;
	entry = readdir(dir);
	while (entry && entry_count++ < 10000)
	{
		if (check_entry(entry, pat_copy, require_dir))
			try_add_match(&files, entry, &match_count);
		entry = readdir(dir);
	}
	return (files);
}

t_nodes	*collect_matches(DIR *dir, char *pattern)
{
	char	*pat_copy;
	int		require_dir;
	t_nodes	*files;

	pat_copy = prepare_pattern(pattern, &require_dir);
	if (!pat_copy)
		return (NULL);
	files = process_directory(dir, pat_copy, require_dir);
	free(pat_copy);
	return (files);
}
