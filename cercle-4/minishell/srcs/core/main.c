/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 03:40:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static char	**duplicate_env_base(char **envp)
{
	int		env_count;
	char	**heap_env;
	int		i;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	heap_env = malloc(sizeof(char *) * (env_count + 2));
	if (!heap_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		heap_env[i] = ft_strdup(envp[i]);
		i++;
	}
	heap_env[i] = NULL;
	return (heap_env);
}

static void	add_shlvl_to_env(char **heap_env)
{
	int		i;
	int		existing_idx;
	char	shlvl_str[20];
	int		shlvl;

	i = 0;
	existing_idx = -1;
	while (heap_env[i])
	{
		if (ft_strncmp(heap_env[i], "SHLVL=", 6) == 0)
			existing_idx = i;
		i++;
	}
	shlvl = 1;
	if (existing_idx != -1)
	{
		shlvl = atoi(heap_env[existing_idx] + 6) + 1;
		if (shlvl > 1000)
			shlvl = 1;
		sprintf(shlvl_str, "SHLVL=%d", shlvl);
		free(heap_env[existing_idx]);
		heap_env[existing_idx] = ft_strdup(shlvl_str);
	}
	else
	{
		shlvl = 1;
		sprintf(shlvl_str, "SHLVL=%d", shlvl);
		heap_env[i] = ft_strdup(shlvl_str);
		heap_env[i + 1] = NULL;
	}
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
		g_state.exit_code = *last_exit_code;
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
	heap_env = duplicate_env_base(envp);
	if (!heap_env)
		return (1);
	add_shlvl_to_env(heap_env);
	g_state.envp = heap_env;
	g_state.interactive_shell = isatty(STDIN_FILENO);
	cmd_exit = handle_command_line_mode(ac, av, &heap_env, &last_exit_code);
	if (cmd_exit != -1)
		return (cmd_exit);
	return (run_interactive_mode(&heap_env, &last_exit_code));
}
