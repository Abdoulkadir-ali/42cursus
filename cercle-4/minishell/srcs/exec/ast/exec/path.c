/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:13:58 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/20 06:59:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Reject a resolved executable path when it targets a directory.
 * @param path Candidate path returned by the PATH lookup.
 * @return The original path or NULL when the path is a directory.
 */
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

/**
 * @brief Build and validate one executable candidate from a PATH entry.
 * @param dir Directory entry extracted from PATH.
 * @param cmd Command name to append to the directory.
 * @return Newly allocated executable path, or NULL when invalid.
 */
static char	*try_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	if (!dir || !*dir)
		dir = ".";
	if (dir[ft_strlen(dir) - 1] == '/')
		temp = ft_strdup(dir);
	else
		temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

/**
 * @brief Search PATH entries until one file match is found.
 * @param cmd Command name requested by the simple command executor.
 * @param path_env Raw PATH variable value.
 * @return Newly allocated executable path, or NULL when none match.
 */
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

/**
 * @brief Resolve a command name into the executable path to run.
 * @param cmd Command token from the AST simple-command node.
 * @param state Shell state used to read the PATH environment variable.
 * @return Newly allocated executable path, or NULL when not found.
 */
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
		return (NULL);
	result = find_executable_in_paths(cmd, path_env);
	return (validate_and_return(result));
}
