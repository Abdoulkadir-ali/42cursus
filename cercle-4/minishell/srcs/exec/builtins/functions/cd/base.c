/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Duplicate an absolute cd target and record its leading slashes.
 * @param path Absolute path supplied to cd.
 * @param leading_slashes Output flag for slash preservation rules.
 * @return Newly allocated duplicate of the absolute path.
 */
static char	*handle_absolute_path(const char *path, size_t *leading_slashes)
{
	size_t	count;
	char	*base;

	count = 0;
	while (path[count] == '/')
		count++;
	base = ft_strdup(path);
	if (!base)
		return (NULL);
	if (count == 2)
		*leading_slashes = 2;
	else
		*leading_slashes = 1;
	return (base);
}

/**
 * @brief Build a logical base path by joining the argument with PWD.
 * @param path Relative path supplied to cd.
 * @param state Shell state used to read PWD.
 * @param leading_slashes Output flag for preserved leading slashes.
 * @return Newly allocated joined path, or NULL when PWD is unavailable.
 */
static char	*handle_relative_with_pwd(const char *path, t_shell_state *state,
		size_t *leading_slashes)
{
	char	*base;
	char	*pwd;

	pwd = ft_get_env("PWD", state->envp);
	if (!pwd || pwd[0] == '\0')
		return (NULL);
	base = join_paths(pwd, path);
	if (base[0] == '/' && base[1] == '/')
		*leading_slashes = 2;
	else if (base[0] == '/')
		*leading_slashes = 1;
	else
		*leading_slashes = 0;
	return (base);
}

/**
 * @brief Build a logical base path by joining the argument with getcwd.
 * @param path Relative path supplied to cd.
 * @param leading_slashes Output flag for preserved leading slashes.
 * @return Newly allocated joined path, or NULL when getcwd fails.
 */
static char	*handle_relative_with_cwd(const char *path, size_t *leading_slashes)
{
	char	*base;
	char	*cwd_dup;

	cwd_dup = get_cwd_dup();
	if (!cwd_dup || cwd_dup[0] == '\0')
	{
		free(cwd_dup);
		return (NULL);
	}
	base = join_paths(cwd_dup, path);
	free(cwd_dup);
	if (base[0] == '/' && base[1] == '/')
		*leading_slashes = 2;
	else if (base[0] == '/')
		*leading_slashes = 1;
	else
		*leading_slashes = 0;
	return (base);
}

/**
 * @brief Build the base path later normalized by the logical cd helpers.
 * @param path Raw path argument selected for cd.
 * @param state Shell state used to inspect the current directory.
 * @param leading_slashes Output count of preserved leading slashes.
 * @return Newly allocated base path used by logical normalization.
 */
char	*build_base_path(const char *path, t_shell_state *state,
		size_t *leading_slashes)
{
	char	*base;

	*leading_slashes = 0;
	if (path[0] == '/')
		return (handle_absolute_path(path, leading_slashes));
	base = handle_relative_with_pwd(path, state, leading_slashes);
	if (base)
		return (base);
	base = handle_relative_with_cwd(path, leading_slashes);
	if (base)
		return (base);
	return (ft_strdup(path));
}
