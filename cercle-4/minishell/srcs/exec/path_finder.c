/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:27:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*check_path_access(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*env_path;
	char	**paths;
	char	*valid_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') || !get_env_path(envp))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	env_path = get_env_path(envp);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	valid_path = check_path_access(cmd, paths);
	free_paths(paths);
	return (valid_path);
}
