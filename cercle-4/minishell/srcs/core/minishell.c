/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:33:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:36:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Handle non-interactive `-c` execution when requested on argv.
 * @param ac Argument count received by the shell entry point.
 * @param av Argument vector that may contain `-c` and the command string.
 * @param state Active shell state used during command execution.
 * @return Command exit status in `-c` mode, or -1 when not in that mode.
 */
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

/**
 * @brief Run the shell main loop for interactive and stdin-driven input.
 * @param state Active shell state shared across command processing.
 * @return Final shell exit status after the read loop ends.
 */
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

/**
 * @brief Release the duplicated environment array owned by shell state.
 * @param envp NULL-terminated environment array to free.
 * @return This function does not return a value.
 */
static void	cleanup_envp(char **envp)
{
	size_t	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

/**
 * @brief Initialize shell state, select runtime mode, and return its status.
 * @param ac Argument count received from `main`.
 * @param av Argument vector used for optional `-c` execution.
 * @param envp Environment array inherited from the parent process.
 * @return Final shell exit status.
 */
int	minishell(int ac, char **av, char **envp)
{
	t_shell_state	state;
	int				cmd_exit;

	if (!init_shell(envp, &state.envp, &state))
		return (1);
	cmd_exit = handle_command_line_mode(ac, av, &state);
	if (cmd_exit != -1)
	{
		cleanup_envp(state.envp);
		return (cmd_exit);
	}
	cmd_exit = run_interactive_mode(&state);
	cleanup_envp(state.envp);
	return (cmd_exit);
}
