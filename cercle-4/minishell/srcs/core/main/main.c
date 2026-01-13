/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:35:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	initialize_environment(char ***heap_env, char **envp)
{
	*heap_env = duplicate_env(envp);
	g_envp = *heap_env;
	g_interactive_shell = isatty(STDIN_FILENO);
}

static int	handle_command_line_mode(int ac, char **av, char ***heap_env,
				int *last_exit_code)
{
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		setup_signals(SIGNAL_HEREDOC);
		process_input(av[2], heap_env, last_exit_code);
		rl_clear_history();
		return (*last_exit_code);
	}
	return (-1);
}

static int	run_interactive_mode(char ***heap_env, int *last_exit_code)
{
	char	*line;

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
		process_input(line, heap_env, last_exit_code);
		g_exit_code = *last_exit_code;
		free(line);
	}
	rl_clear_history();
	return (*last_exit_code);
}

int	main(int ac, char **av, char **envp)
{
	char	**heap_env;
	int		last_exit_code;
	int		cmd_exit;

	(void)ac;
	(void)av;
	last_exit_code = 0;
	initialize_environment(&heap_env, envp);
	cmd_exit = handle_command_line_mode(ac, av, &heap_env, &last_exit_code);
	if (cmd_exit != -1)
		return (cmd_exit);
	return (run_interactive_mode(&heap_env, &last_exit_code));
}
