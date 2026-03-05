/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:07:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	builtin_colon(char **args, t_shell_state *state)
{
	(void)args;
	(void)state;
	return (0);
}

static const t_builtin_def	g_builtins[] = {
{"echo", ft_echo},
{"cd", ft_cd},
{"pwd", ft_pwd},
{"export", ft_export},
{"unset", ft_unset},
{"env", ft_env},
{"exit", ft_exit},
{":", builtin_colon},
{NULL, NULL}
};

int	is_builtin(char *cmd, char **args, int is_quoted)
{
	int	i;

	(void)is_quoted;
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "."))
		return (1);
	if (!ft_strcmp(cmd, "env") && args && args[1])
		return (0);
	i = 0;
	while (g_builtins[i].name)
	{
		if (!ft_strcmp(cmd, g_builtins[i].name))
			return (1);
		i++;
	}
	return (0);
}

static int	exec_dot_builtin(char **args)
{
	if (!args[1])
	{
		ft_puterror(".: filename argument required\n");
		ft_puterror(".: usage: . filename [arguments]\n");
		return (2);
	}
	return (0);
}

int	exec_builtin(char **args, t_shell_state *state)
{
	int	i;

	if (!ft_strcmp(args[0], "."))
		return (exec_dot_builtin(args));
	i = 0;
	while (g_builtins[i].name)
	{
		if (!ft_strcmp(args[0], g_builtins[i].name))
			return (g_builtins[i].func(args, state));
		i++;
	}
	return (0);
}
