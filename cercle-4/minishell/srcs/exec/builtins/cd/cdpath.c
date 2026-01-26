/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:42:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 03:39:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_cd_path(char **args, char **envp)
{
	char	*path;
	char	*cdpath;
	char	*candidate;

	if (!args[1] || (ft_strncmp(args[1], "--", 3) == 0))
	{
		path = resolve_home(envp);
		if (!path)
			return (NULL);
		if (path != get_env_val_simple("HOME", envp))
			return (ft_strdup(path));
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_val_simple("OLDPWD", envp);
		if (!path)
		{
			ft_puterror("cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_putendl_fd(path, 1);
	}
	else
		path = args[1];
	if (path && path[0] != '/' && !ft_strchr(path, '/'))
	{
		cdpath = get_env_val_simple("CDPATH", envp);
		candidate = cdpath_find(path, cdpath);
		if (candidate)
		{
			if (ft_strchr(candidate, '/'))
				ft_putendl_fd(candidate, 1);
			return (candidate);
		}
	}
	return (path);
}

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

static int	candidate_is_dir(const char *path)
{
	struct stat	sb;

	/* Candidate must be a directory and be accessible (execute permission)
		so that we don't pick CDPATH entries that exist but cannot be entered */
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode) && access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*cdpath_find(const char *name, char *cdpath)
{
	int		start;
	int		cplen;
	int		end;
	int		toklen;
	char	*entry;
	char	*candidate;

	if (!cdpath)
		return (NULL);
	start = 0;
	cplen = ft_strlen(cdpath);
	while (start <= cplen)
	{
		end = start;
		while (end < cplen && cdpath[end] != ':')
			end++;
		toklen = end - start;
		if (toklen == 0)
			entry = NULL;
		else
			entry = ft_substr(cdpath, start, toklen);
		candidate = build_candidate(entry, name);
		if (entry)
			free(entry);
		if (candidate)
		{
			if (candidate_is_dir(candidate))
				return (candidate);
			free(candidate);
		}
		start = end + 1;
	}
	return (NULL);
}
