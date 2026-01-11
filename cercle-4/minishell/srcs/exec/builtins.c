/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 14:19:27 by abdoali          ###   ########.fr       */
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

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		int k = 1;
		while (args[i][k] == 'n') k++;
		if (args[i][k] == '\0')
		{
			newline = 0;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	ft_cd(char **args)
{
	if (!args[1])
		return (0);
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	status;

	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		if (!is_number(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		status = ft_atoi(args[1]);
	}
	else
		status = 0;
	exit(status);
	return (status);
}

/* Dispatcher */
int	is_builtin(char *cmd, char **args)
{
	if (!cmd)
		return (0);
	if (is_cmd(cmd, "echo") || is_cmd(cmd, "cd")
		|| is_cmd(cmd, "pwd") || is_cmd(cmd, "export")
		|| is_cmd(cmd, "unset") || (is_cmd(cmd, "env") && (!args || !args[1]))
		|| is_cmd(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(char **args, char ***envp)
{
	if (is_cmd(args[0], "echo"))
		return (ft_echo(args));
	if (is_cmd(args[0], "cd"))
		return (ft_cd(args));
	if (is_cmd(args[0], "pwd"))
		return (ft_pwd());
	if (is_cmd(args[0], "env"))
		return (ft_env(*envp));
	if (is_cmd(args[0], "exit"))
		return (ft_exit(args));
	if (is_cmd(args[0], "export"))
		return (ft_export(args, envp));
	if (is_cmd(args[0], "unset"))
		return (ft_unset(args, envp));
	return (0);
}
