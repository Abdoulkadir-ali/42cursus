/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:38:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* The low-level wildcard helpers (match_loop, should_skip_entry,
 * check_entry, prepare_pattern) live in match/loop.c and match/helpers.c.
 * This file keeps higher-level functions that use those helpers. */

/**
 * @brief Duplicate and append one matching entry to the result list.
 */
static void	add_match(t_nodes **files, struct dirent *entry, int *match_count)
{
	if ((*match_count)++ <= 100)
		ft_lstadd_back(files, ft_lstnew(ft_strdup(entry->d_name)));
}

/**
 * @brief Scan one directory stream and collect entries that match a pattern.
 */
t_nodes	*process_directory(DIR *dir, char *pat_copy, int require_dir)
{
	t_nodes			*files;
	int				match_count;
	struct dirent	*entry;

	files = NULL;
	match_count = 0;
	entry = readdir(dir);
	while (entry && match_count < 10000)
	{
		if (check_entry(entry, pat_copy, require_dir))
			add_match(&files, entry, &match_count);
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
