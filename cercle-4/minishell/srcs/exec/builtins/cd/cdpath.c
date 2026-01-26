/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:42:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:13:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*handle_home(char **envp)
{
	char	*path;

	path = resolve_home(envp);
	if (!path)
		return (NULL);
	if (path != get_env_val_simple("HOME", envp))
		return (ft_strdup(path));
	return (path);
}

static char	*handle_oldpwd(char **envp)
{
	char	*path;

	path = get_env_val_simple("OLDPWD", envp);
	if (!path)
	{
		ft_puterror("cd: OLDPWD not set\n");
		return (NULL);
	}
	ft_putendl_fd(path, 1);
	return (path);
}

static char	*get_path_from_args(char **args, char **envp)
{
	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
		return (handle_home(envp));
	else if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_oldpwd(envp));
	else
		return (args[1]);
}

static char	*check_cdpath(char *path, char **envp)
{
	char	*cdpath;
	char	*candidate;

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

char	*get_cd_path(char **args, char **envp)
{
	char	*path;

	path = get_path_from_args(args, envp);
	return (check_cdpath(path, envp));
}
