/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 23:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:32:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	builtin_colon(char **args, t_shell_state *state)
{
	(void)args;
	(void)state;
	return (0);
}

void	init_builtin_entry(t_builtin_def *entry, const char *name,
		int (*func)(char **, t_shell_state *))
{
	entry->name = (char *)name;
	entry->func = func;
}

void	init_builtins(t_builtin_def *builtins)
{
	init_builtin_entry(&builtins[0], "echo", ft_echo);
	init_builtin_entry(&builtins[1], "cd", ft_cd);
	init_builtin_entry(&builtins[2], "pwd", ft_pwd);
	init_builtin_entry(&builtins[3], "export", ft_export);
	init_builtin_entry(&builtins[4], "unset", ft_unset);
	init_builtin_entry(&builtins[5], "env", ft_env);
	init_builtin_entry(&builtins[6], "exit", ft_exit);
	init_builtin_entry(&builtins[7], ":", builtin_colon);
	builtins[8].name = NULL;
	builtins[8].func = NULL;
}

const t_builtin_def	*get_builtins(void)
{
	static t_builtin_def	builtins[10];
	static int				initialized;

	if (!initialized)
	{
		init_builtins(builtins);
		initialized = 1;
	}
	return (builtins);
}
