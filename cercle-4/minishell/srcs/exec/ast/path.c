/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/13 23:42:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_path_env(void)
{
	return (getenv("PATH"));
}

static char	**split_path(char *path)
{
	return (ft_split(path, ':'));
}

static void	free_paths(char **paths)
{
	int	j;

	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
}

static char	*find_executable_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	char	*result;

	(void)envp;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_path_env();
	if (!path)
		return (NULL);
	paths = split_path(path);
	if (!paths)
		return (NULL);
	result = find_executable_in_paths(cmd, paths);
	free_paths(paths);
	return (result);
}
