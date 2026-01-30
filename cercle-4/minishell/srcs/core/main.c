/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:33:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:12:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	handle_command_line_mode(int ac, char **av, t_shell_state *state)
{
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		setup_signals(SIGNAL_HEREDOC);
		process_input(av[2], state);
		rl_clear_history();
		return (state->exit_code);
	}
	return (-1);
}

static int	run_interactive_mode(t_shell_state *state)
{
	char	*line;

	setup_signals(SIGNAL_INTERACTIVE);
	while (1)
	{
		state->syntax_error = 0;
		line = get_command_line(state);
		if (!line)
		{
			if (state->interactive_shell)
				ft_printf_fd(2, "exit\n");
			break ;
		}
		process_input(line, state);
		free(line);
	}
	rl_clear_history();
	if (state->syntax_error)
		return (2);
	return (state->exit_code);
}

int	main(int ac, char **av, char **envp)
{
	char			**heap_env;
	int				cmd_exit;
	t_shell_state	state;

	if (init_shell(envp, &heap_env, &state))
		return (1);
	cmd_exit = handle_command_line_mode(ac, av, &state);
	if (cmd_exit != -1)
		return (cmd_exit);
	return (run_interactive_mode(&state));
}
