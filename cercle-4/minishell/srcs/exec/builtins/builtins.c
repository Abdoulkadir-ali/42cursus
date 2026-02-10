/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 04:08:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	wrap_echo(char **args, t_shell_state *state)
{
	(void)state;
	return (ft_echo(args));
}

static int	wrap_pwd(char **args, t_shell_state *state)
{
	(void)args;
	return (ft_pwd(state));
}

static int	wrap_env(char **args, t_shell_state *state)
{
	(void)args;
	return (ft_env(state));
}

static int	wrap_colon(char **args, t_shell_state *state)
{
	(void)args;
	(void)state;
	return (0);
}

typedef struct s_builtin_def
{
	const char	*name;
	int			(*func)(char **, t_shell_state *);
}			t_builtin_def;

static const t_builtin_def	g_builtins[] = {
{"echo", wrap_echo},
{"cd", ft_cd},
{"pwd", wrap_pwd},
{"export", ft_export},
{"unset", ft_unset},
{"env", wrap_env},
{"exit", ft_exit},
{":", wrap_colon},
{NULL, NULL}
};

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
	int	i;

	(void)is_quoted;
	if (!cmd)
		return (0);
	if (is_cmd(cmd, "."))
		return (1);
	if (is_cmd(cmd, "env") && args && args[1])
		return (0);
	i = 0;
	while (g_builtins[i].name)
	{
		if (is_cmd(cmd, (char *)g_builtins[i].name))
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

	if (is_cmd(args[0], "."))
		return (exec_dot_builtin(args));
	i = 0;
	while (g_builtins[i].name)
	{
		if (is_cmd(args[0], (char *)g_builtins[i].name))
			return (g_builtins[i].func(args, state));
		i++;
	}
	return (0);
}
