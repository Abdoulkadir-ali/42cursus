/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:41 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:43 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Resolve `cd -` by reading and printing OLDPWD.
 * @param state Shell state used to read OLDPWD.
 * @return Newly allocated target path, or NULL when OLDPWD is unset.
 */
static char	*handle_oldpwd(t_shell_state *state)
{
	char	*path;

	path = ft_get_env("OLDPWD", state->envp);
	if (!path)
	{
		ft_puterror("cd: OLDPWD not set\n");
		return (NULL);
	}
	ft_putendl_fd(path, 1);
	return (ft_strdup(path));
}

/**
 * @brief Select the raw path operand used by the cd builtin.
 * @param args Argument vector passed to cd.
 * @param state Shell state used when HOME or OLDPWD is required.
 * @return Newly allocated raw cd target path.
 */
static char	*get_path_from_args(char **args, t_shell_state *state)
{
	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
		return (resolve_home(state));
	else if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_oldpwd(state));
	else
		return (ft_strdup(args[1]));
}

/**
 * @brief Apply CDPATH lookup when the cd target is a bare relative name.
 * @param path Current cd target candidate.
 * @param state Shell state used to read CDPATH.
 * @return Replacement path from CDPATH, or the original candidate.
 */
static char	*check_cdpath(char *path, t_shell_state *state)
{
	char	*cdpath;
	char	*candidate;

	if (path && path[0] != '/' && !ft_strchr(path, '/'))
	{
		cdpath = ft_get_env("CDPATH", state->envp);
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

/**
 * @brief Resolve the final target path used by the cd builtin.
 * @param args Argument vector passed to cd.
 * @param state Shell state used to resolve HOME, OLDPWD, and CDPATH.
 * @return Newly allocated path that cd should attempt to enter.
 */
char	*get_cd_path(char **args, t_shell_state *state)
{
	char	*path;

	path = get_path_from_args(args, state);
	return (check_cdpath(path, state));
}
