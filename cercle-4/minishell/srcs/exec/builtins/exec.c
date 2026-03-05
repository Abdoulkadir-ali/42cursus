/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:32:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char *cmd, char **args, int is_quoted)
{
	int					i;
	const t_builtin_def	*builtins;

	(void)is_quoted;
	builtins = get_builtins();
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "."))
		return (1);
	if (!ft_strcmp(cmd, "env") && args && args[1])
		return (0);
	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd, builtins[i].name))
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
	int					i;
	const t_builtin_def	*builtins;

	builtins = get_builtins();
	if (!ft_strcmp(args[0], "."))
		return (exec_dot_builtin(args));
	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(args[0], builtins[i].name))
			return (builtins[i].func(args, state));
		i++;
	}
	return (0);
}
