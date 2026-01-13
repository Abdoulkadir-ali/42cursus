/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 01:10:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int	ft_cd(char **args, char ***envp)
{
    char	cwd[1024];
    char	oldcwd[1024];
    char	*path;

    if (args[1] && args[2])
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        return (1);
    }
    if (!args[1] || (ft_strncmp(args[1], "--", 3) == 0))
    {
        path = get_env_val_simple("HOME", *envp);
        if (!path)
        {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            return (1);
        }
    }
    else if (ft_strncmp(args[1], "-", 2) == 0)
    {
        path = get_env_val_simple("OLDPWD", *envp);
        if (!path)
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
            return (1);
        }
        ft_putendl_fd(path, 1);
    }
    else
        path = args[1];
    if (args[1] && args[2])
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        return (1);
    }
    getcwd(oldcwd, sizeof(oldcwd));
    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        return (1);
    }
    getcwd(cwd, sizeof(cwd));
    ft_set_env("OLDPWD", oldcwd, envp);
    ft_set_env("PWD", cwd, envp);
    return (0);
}