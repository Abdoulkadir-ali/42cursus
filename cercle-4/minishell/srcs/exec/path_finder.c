/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/12 19:28:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

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
	char	*first_non_exec;
	struct stat	st;

	i = 0;
	first_non_exec = NULL;
	while (paths[i])
	{
		if (paths[i][0] == '\0')
		{
			i++;
			continue;
		}
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
			{
				if (access(path, X_OK) == 0)
				{
					if (first_non_exec)
						free(first_non_exec);
					return (path);
				}
				if (!first_non_exec)
					first_non_exec = path;
				else
					free(path);
			}
			else
				free(path);
		}
		else
			free(path);
		i++;
	}
	return (first_non_exec);
}

char	*find_path(char *cmd, char **envp)
{
	char	*env_path;
	char	**paths;
	char	*valid_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env_path = get_env_path(envp);
	if (!env_path)
		env_path = "/usr/local/bin:/usr/bin:/bin";
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	valid_path = check_path_access(cmd, paths);
	free_paths(paths);
	return (valid_path);
}
