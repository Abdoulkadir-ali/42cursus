/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 04:49:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

static char	*get_env_val_simple(char *key, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	validate_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_puterror("cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static char	*get_cd_path(char **args, char **envp)
{
	char	*path;

	if (!args[1] || (ft_strncmp(args[1], "--", 3) == 0))
	{
		path = get_env_val_simple("HOME", envp);
		if (!path)
		{
			/* Fallback to the password database when HOME isn't present
			   in the environment (e.g., when running under `env -i`). */
			struct passwd *pw = getpwuid(getuid());
			if (pw && pw->pw_dir)
				return (pw->pw_dir);
			ft_puterror("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_val_simple("OLDPWD", envp);
		if (!path)
		{
			ft_puterror("cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_putendl_fd(path, 1);
	}
	else
		path = args[1];
	return (path);
}

static int	perform_cd(char *path, char ***envp)
{
	char	cwd[1024];
	char	oldcwd[1024];

	getcwd(oldcwd, sizeof(oldcwd));
	if (chdir(path) == -1)
	{
		ft_puterror("cd: %s: ", path);
		perror(NULL);
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	ft_set_env("OLDPWD", oldcwd, envp);
	ft_set_env("PWD", cwd, envp);
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
