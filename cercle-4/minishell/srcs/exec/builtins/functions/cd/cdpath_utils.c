/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:14:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*build_candidate(char *entry, const char *name)
{
	char	*candidate;
	char	*cwd;
	char	*abs_candidate;

	if (!entry)
		return (ft_strdup(name));
	candidate = join_paths(entry, (char *)name);
	if (!candidate)
		return (NULL);
	if (entry[0] != '/')
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			abs_candidate = join_paths(cwd, candidate);
			free(candidate);
			candidate = abs_candidate;
			free(cwd);
		}
	}
	return (candidate);
}

static char	*get_next_entry(char *cdpath, int *start)
{
	int		end;
	int		cplen;
	int		toklen;
	char	*entry;

	end = *start;
	cplen = ft_strlen(cdpath);
	while (end < cplen && cdpath[end] != ':')
		end++;
	toklen = end - *start;
	if (toklen == 0)
		entry = NULL;
	else
		entry = ft_substr(cdpath, *start, toklen);
	*start = end + 1;
	return (entry);
}

static char	*check_candidate(char *candidate)
{
	struct stat	sb;

	if (stat(candidate, &sb) == 0 && S_ISDIR(sb.st_mode)
		&& access(candidate, X_OK) == 0)
		return (candidate);
	free(candidate);
	return (NULL);
}

char	*cdpath_find(const char *name, char *cdpath)
{
	int		start;
	char	*entry;
	char	*candidate;

	if (!cdpath)
		return (NULL);
	start = 0;
	while (1)
	{
		entry = get_next_entry(cdpath, &start);
		if (!entry)
			break ;
		candidate = build_candidate(entry, name);
		free(entry);
		if (candidate)
		{
			candidate = check_candidate(candidate);
			if (candidate)
				return (candidate);
		}
	}
	return (NULL);
}
