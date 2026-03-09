/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Build one candidate absolute path from a CDPATH entry.
 * @param entry One directory entry extracted from CDPATH.
 * @param name Relative directory name requested by cd.
 * @return Newly allocated candidate path, or NULL on allocation failure.
 */
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

/**
 * @brief Extract the next colon-delimited CDPATH entry.
 * @param cdpath Raw CDPATH string.
 * @param start Cursor updated to the next unread offset.
 * @return Newly allocated entry, or NULL for an empty token.
 */
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

/**
 * @brief Accept a CDPATH candidate only when it names an accessible directory.
 * @param candidate Candidate path built from one CDPATH entry.
 * @return The same candidate on success, otherwise NULL.
 */
static char	*check_candidate(char *candidate)
{
	struct stat	sb;

	if (stat(candidate, &sb) == 0 && S_ISDIR(sb.st_mode)
		&& access(candidate, X_OK) == 0)
		return (candidate);
	free(candidate);
	return (NULL);
}

/**
 * @brief Search CDPATH for the first directory matching a bare cd target.
 * @param name Relative directory name requested by cd.
 * @param cdpath Raw CDPATH value.
 * @return Newly allocated matching directory path, or NULL when absent.
 */
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
