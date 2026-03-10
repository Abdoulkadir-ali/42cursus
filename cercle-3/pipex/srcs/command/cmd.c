/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:11:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 17:07:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*try_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*result;
	int		i;

	i = -1;
	while (paths[++i])
	{
		result = try_path(paths[i], cmd);
		if (result)
		{
			free_args(paths);
			return (result);
		}
	}
	free_args(paths);
	return (NULL);
}

static char	*find_command_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!cmd || access(cmd, X_OK) == 0)
		return (cmd);
	path_env = getenv("PATH");
	if (!path_env)
		return (cmd);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (cmd);
	result = search_in_paths(paths, cmd);
	if (result)
		return (result);
	return (cmd);
}

int	execute_command(char *cmd)
{
	extern char	**environ;
	char		**args;
	char		*cmd_path;
	int			saved_errno;

	args = parse_command(cmd);
	if (!args || !args[0])
	{
		if (args)
			free_args(args);
		exit(127);
	}
	cmd_path = find_command_path(args[0]);
	execve(cmd_path, args, environ);
	saved_errno = errno;
	if (cmd_path != args[0])
		free(cmd_path);
	perror(args[0]);
	free_args(args);
	if (saved_errno == ENOENT)
		exit(127);
	exit(126);
}
