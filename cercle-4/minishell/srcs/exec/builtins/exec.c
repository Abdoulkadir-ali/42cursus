/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Check whether a command name should run through builtin dispatch.
 * @param cmd Command name from the parsed argument vector.
 * @param args Full argv used for special builtin cases such as env.
 * @return True when the command is handled internally, else false.
 */
bool	is_builtin(char *cmd, char **args)
{
	size_t				i;
	const t_builtin_def	*builtins;

	builtins = get_builtins();
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "env") && args && args[1])
		return (false);
	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd, builtins[i].name))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Dispatch a builtin command through the registered builtin table.
 * @param args Full argument vector for the builtin command.
 * @param state Active shell state passed to the builtin implementation.
 * @return Status code returned by the selected builtin.
 */
int	exec_builtin(char **args, t_shell_state *state)
{
	size_t				i;
	const t_builtin_def	*builtins;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(args[0], builtins[i].name))
			return (builtins[i].func(args, state));
		i++;
	}
	return (0);
}
