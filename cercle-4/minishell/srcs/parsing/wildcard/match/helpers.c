/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 06:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 03:02:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	match_pattern(char *pattern, char *str)
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

int	should_skip_entry(struct dirent *entry, char *pattern)
{
	char	pat_first;

	pat_first = pattern[0];
	if (pat_first == '\001' && pattern[1])
		pat_first = pattern[1];
	if (entry->d_name[0] == '.' && pat_first != '.')
		return (1);
	if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
		return (1);
	if (ft_strcmp(entry->d_name, pattern) == 0)
		return (1);
	return (0);
}

void	try_add_match(t_nodes **files, struct dirent *entry, int *match_count)
{
	char	*dup;

	if ((*match_count)++ <= 100)
	{
		dup = ft_strdup(entry->d_name);
		ft_lstadd_back(files, ft_lstnew(dup));
	}
}

char	*prepare_pattern(char *pattern, int *require_dir)
{
	char	*pat_copy;

	pat_copy = ft_strdup(pattern);
	if (!pat_copy)
		return (NULL);
	*require_dir = 0;
	while (ft_strlen(pat_copy) > 0 && pat_copy[ft_strlen(pat_copy) - 1] == '/')
	{
		pat_copy[ft_strlen(pat_copy) - 1] = '\0';
		(*require_dir) = 1;
	}
	return (pat_copy);
}

int	check_entry(struct dirent *entry, char *pat_copy, int require_dir)
{
	struct stat	st;

	if (should_skip_entry(entry, pat_copy))
		return (0);
	if (!match_pattern(pat_copy, entry->d_name))
		return (0);
	if (require_dir)
	{
		if (entry->d_type == DT_DIR)
			return (1);
		else if (entry->d_type == DT_UNKNOWN)
		{
			if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode))
				return (1);
		}
		return (0);
	}
	return (1);
}
