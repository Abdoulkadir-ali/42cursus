/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:58:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*handle_absolute_path(const char *path, int *leading_slashes)
{
	int		count;
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

static char	*handle_relative_with_pwd(const char *path, t_shell_state *state,
		int *leading_slashes)
{
	char	*base;
	char	*pwd;

	pwd = get_env_val_simple("PWD", state);
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

static char	*handle_relative_with_cwd(const char *path, int *leading_slashes)
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

char	*build_base_path(const char *path, t_shell_state *state,
		int *leading_slashes)
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
