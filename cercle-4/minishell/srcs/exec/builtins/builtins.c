/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 03:39:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_cmd(char *arg, char *cmd)
{
	if (!arg || !cmd)
		return (0);
	if (ft_strncmp(arg, cmd, ft_strlen(cmd) + 1) == 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd, char **args, int is_quoted)
{
	(void)is_quoted;
	if (!cmd)
		return (0);
	if (is_cmd(cmd, "echo") || is_cmd(cmd, "cd") || is_cmd(cmd, "pwd")
		|| is_cmd(cmd, "export") || is_cmd(cmd, "unset") || (is_cmd(cmd, "env")
			&& (!args || !args[1])) || is_cmd(cmd, "exit") || is_cmd(cmd, ":")
		|| is_cmd(cmd, "."))
		return (1);
	return (0);
}

int	exec_builtin(char **args, char ***envp)
{
	if (is_cmd(args[0], "echo"))
		return (ft_echo(args));
	if (is_cmd(args[0], "cd"))
		return (ft_cd(args, envp));
	if (is_cmd(args[0], "pwd"))
		return (ft_pwd(*envp));
	if (is_cmd(args[0], "env"))
		return (ft_env(*envp));
	if (is_cmd(args[0], "exit"))
		return (ft_exit(args));
	if (is_cmd(args[0], "export"))
		return (ft_export(args, envp));
	if (is_cmd(args[0], "unset"))
		return (ft_unset(args, envp));
	if (is_cmd(args[0], ":"))
		return (0);
	if (is_cmd(args[0], "."))
	{
		if (!args[1])
		{
			ft_puterror(".: filename argument required\n");
			ft_puterror(".: usage: . filename [arguments]\n");
			return (2);
		}
		return (0);
	}
	return (0);
}
