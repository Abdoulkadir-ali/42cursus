/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:26:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Scan one directory stream and collect entries that match a pattern.
 * @param dir Open directory stream positioned at the start of the scan.
 * @param pat_copy Normalized wildcard pattern.
 * @param require_dir Non-zero when only directory matches are accepted.
 * @return Linked list of collected filenames, or NULL when no match is stored.
 */
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

/**
 * @brief Prepare a pattern and collect every directory entry that matches it.
 * @param dir Open directory stream used for enumeration.
 * @param pattern Raw wildcard pattern from the caller.
 * @return Linked list of collected filenames, or NULL on failure.
 */
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
