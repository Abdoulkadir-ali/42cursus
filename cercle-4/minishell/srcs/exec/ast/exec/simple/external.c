/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 05:12:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:56:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Logic executed in the child process during an external command run.
 * @param path Resolved absolute path to the executable file.
 * @param node AST node containing the command and arguments.
 * @param state Initialized shell state passed to the child.
 */
static void	child_execution(char *path, t_ast *node, t_shell_state *state)
{
	struct stat	st;

	setup_child_signals();
	apply_assigns_to_state(node, state);
	ft_set_env("_", path, state);
	execve(path, node->args, state->envp);
	if (errno == ENOENT)
	{
		ft_puterror("%s: No such file or directory\n", node->args[0]);
		exit(127);
	}
	if (errno == EACCES)
	{
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			ft_puterror("%s: Is a directory\n", node->args[0]);
		else
			ft_puterror("%s: Permission denied\n", node->args[0]);
		exit(126);
	}
	ft_puterror("%s: ", node->args[0]);
	perror(NULL);
	exit(1);
}

/**
 * @brief Fork and manage the execution of an external binary.
 * @param path Absolute path to the executable.
 * @param node AST node containing arguments for the command.
 * @param state Active shell state.
 * @return Normalized exit status of the child process.
 */
static int	run_external_command(char *path, t_ast *node, t_shell_state *state)
{
	pid_t	pid;
	int		status;

	pid = fork_protected();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_execution(path, node, state);
	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	free(path);
	return (handle_wait_status(status));
}

/**
 * @brief Orthestrate external command lookup and execution.
 * @param node AST node whose word is an external command candidate.
 * @param state Active shell state used for PATH lookup and environment.
 * @return Final exit status of the external command attempt.
 */
int	exec_external_with_lookup(t_ast *node, t_shell_state *state)
{
	char	*path;
	char	**saved_env;
	int		status;

	if (save_and_apply_assigns(node, state, &saved_env))
		return (1);
	path = find_path(node->args[0], state);
	restore_env_and_free(state, saved_env);
	if (!path)
		return (report_command_not_found(node->args[0], state));
	status = run_external_command(path, node, state);
	return (status);
}
