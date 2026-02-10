/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:42:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/10 22:44:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*handle_home(t_shell_state *state)
{
	return (resolve_home(state));
}

static char	*handle_oldpwd(t_shell_state *state)
{
	char	*path;

	path = get_env_val_simple("OLDPWD", state);
	if (!path)
	{
		ft_puterror("cd: OLDPWD not set\n");
		return (NULL);
	}
	ft_putendl_fd(path, 1);
	return (ft_strdup(path));
}

static char	*get_path_from_args(char **args, t_shell_state *state)
{
	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
		return (handle_home(state));
	else if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_oldpwd(state));
	else
		return (ft_strdup(args[1]));
}

static char	*check_cdpath(char *path, t_shell_state *state)
{
	char	*cdpath;
	char	*candidate;

	if (path && path[0] != '/' && !ft_strchr(path, '/'))
	{
		cdpath = get_env_val_simple("CDPATH", state);
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

char	*get_cd_path(char **args, t_shell_state *state)
{
	char	*path;

	path = get_path_from_args(args, state);
	return (check_cdpath(path, state));
}
