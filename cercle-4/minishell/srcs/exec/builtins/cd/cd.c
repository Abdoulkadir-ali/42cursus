/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 04:09:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	validate_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_puterror("cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	perform_cd(char *path, char ***envp)
{
	char	*oldpwd;
	char	cwd[1024];
	int		rc;
	char	*newpwd;

	oldpwd = get_env_val_simple("PWD", *envp);
	if (!oldpwd || oldpwd[0] == '\0')
		oldpwd = get_cwd_dup();
	else
		oldpwd = ft_strdup(oldpwd);
	rc = chdir(path);
	if (rc == -1)
	{
		ft_puterror("cd: %s: ", path);
		perror(NULL);
		free(oldpwd);
		return (1);
	}
	newpwd = normalize_logical(path, *envp);
	if (!newpwd)
	{
		if (getcwd(cwd, sizeof(cwd)))
			newpwd = ft_strdup(cwd);
		else
			newpwd = ft_strdup("");
	}
	ft_set_env("OLDPWD", oldpwd, envp);
	ft_set_env("PWD", newpwd, envp);
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	ft_cd(char **args, char ***envp)
{
	char	*path;

	if (validate_cd_args(args))
		return (1);
	path = get_cd_path(args, *envp);
	if (!path)
		return (1);
	return (perform_cd(path, envp));
}
