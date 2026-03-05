/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:20:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:21:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*validate_and_return(char *path)
{
	struct stat	st;

	if (path && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static char	*try_path(char *dir, char *cmd)
{
	char		*temp;
	char		*full_path;
	struct stat	st;

	if (!dir || !*dir)
		dir = ".";
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
	{
		if (stat(full_path, &st) == 0 && !S_ISDIR(st.st_mode))
			return (full_path);
	}
	free(full_path);
	return (NULL);
}

static char	*find_executable_in_paths(char *cmd, char *path_env)
{
	char	*start;
	char	*end;
	char	*dir;
	char	*res;

	start = path_env;
	while (start)
	{
		end = ft_strchr(start, ':');
		if (end)
			dir = ft_substr(start, 0, end - start);
		else
			dir = ft_strdup(start);
		res = try_path(dir, cmd);
		free(dir);
		if (res)
			return (res);
		if (!end)
			break ;
		start = end + 1;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_shell_state *state)
{
	char	*path_env;
	char	*result;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = ft_get_env("PATH", state->envp);
	if (!path_env)
		path_env = "/bin:/usr/bin:/usr/local/bin";
	if (!*path_env)
		return (NULL);
	result = find_executable_in_paths(cmd, path_env);
	return (validate_and_return(result));
}
