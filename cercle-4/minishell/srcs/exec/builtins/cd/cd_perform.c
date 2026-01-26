/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_perform.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:45:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_oldpwd(t_shell_state *state)
{
	char	*oldpwd;

	oldpwd = get_env_val_simple("PWD", state);
	if (!oldpwd || oldpwd[0] == '\0')
		oldpwd = get_cwd_dup();
	else
		oldpwd = ft_strdup(oldpwd);
	return (oldpwd);
}

static int	change_directory(char *path, t_shell_state *state)
{
	char	*norm_path;
	int		rc;

	norm_path = normalize_logical(path, state);
	if (norm_path)
		rc = chdir(norm_path);
	else
		rc = chdir(path);
	free(norm_path);
	return (rc);
}

static int	handle_cd_error(char *path, char *oldpwd, char *norm_path)
{
	if (path[0] == '/')
		return (0);
	ft_puterror("cd: %s: ", path);
	perror(NULL);
	free(oldpwd);
	free(norm_path);
	return (1);
}

static char	*get_newpwd(char *path, t_shell_state *state)
{
	char	cwd[1024];
	char	*newpwd;

	newpwd = normalize_logical(path, state);
	if (!newpwd)
	{
		if (getcwd(cwd, sizeof(cwd)))
			newpwd = ft_strdup(cwd);
		else
			newpwd = ft_strdup("");
	}
	return (newpwd);
}

int	perform_cd(char *path, t_shell_state *state)
{
	char	*oldpwd;
	int		rc;
	char	*newpwd;

	oldpwd = get_oldpwd(state);
	rc = change_directory(path, state);
	if (rc == -1)
		return (handle_cd_error(path, oldpwd, NULL));
	newpwd = get_newpwd(path, state);
	ft_set_env("OLDPWD", oldpwd, state);
	ft_set_env("PWD", newpwd, state);
	free(oldpwd);
	free(newpwd);
	return (0);
}
