
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/11 14:19:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		last_exit_code;
	char	**heap_env;

	(void)ac;
	(void)av;
	last_exit_code = 0;
		  heap_env = duplicate_env(envp);
		  g_envp = heap_env;
		  g_interactive_shell = isatty(STDIN_FILENO);
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		setup_signals(SIGNAL_HEREDOC);
		process_input(av[2], &heap_env, &last_exit_code);
		rl_clear_history();
		return (last_exit_code);
	}
	setup_signals(SIGNAL_INTERACTIVE);
	while (1)
	{
		line = get_command_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_printf_fd(2, "exit\n");
			break ;
		}
		process_input(line, &heap_env, &last_exit_code);
		g_exit_code = last_exit_code;
		free(line);
	}
	rl_clear_history();
	return (last_exit_code);
}
