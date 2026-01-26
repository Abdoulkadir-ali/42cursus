/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/22 21:17:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <sys/stat.h>

static int	match_pattern(char *pattern, char *str)
{
	char	*star;
	char	*str_start;

	star = NULL;
	str_start = str;
	if (!match_loop(&pattern, &str, &star, &str_start))
		return (0);
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

static int	should_skip_entry(struct dirent *entry, char *pattern)
{
	if (entry->d_name[0] == '.' && pattern[0] != '.')
		return (1);
	if (ft_strcmp(entry->d_name, pattern) == 0)
		return (1);
	return (0);
}

static void	try_add_match(t_nodes **files, struct dirent *entry,
		int *match_count)
{
	char	*dup;

	if ((*match_count)++ <= 100)
	{
		dup = ft_strdup(entry->d_name);
		ft_lstadd_back(files, ft_lstnew(dup));
	}
}

t_nodes	*collect_matches(DIR *dir, char *pattern)
{
	struct dirent	*entry;
	t_nodes			*files;
	int				match_count;
	int				entry_count;
	char			*pat_copy;
	int				require_dir;
	struct stat		st;

	files = NULL;
	match_count = 0;
	entry_count = 0;
	require_dir = 0;
	pat_copy = ft_strdup(pattern);
	if (!pat_copy)
		return (NULL);
	while (ft_strlen(pat_copy) > 0 && pat_copy[ft_strlen(pat_copy) - 1] == '/')
	{
		pat_copy[ft_strlen(pat_copy) - 1] = '\0';
		require_dir = 1;
	}
	entry = readdir(dir);
	while (entry && entry_count++ < 10000)
	{
		if (should_skip_entry(entry, pat_copy))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pat_copy, entry->d_name))
		{
			if (require_dir)
			{
				if (entry->d_type == DT_DIR)
					try_add_match(&files, entry, &match_count);
				else if (entry->d_type == DT_UNKNOWN)
				{
					if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode))
						try_add_match(&files, entry, &match_count);
				}
			}
			else
				try_add_match(&files, entry, &match_count);
		}
		entry = readdir(dir);
	}
	free(pat_copy);
	return (files);
}
