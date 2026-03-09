/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:24:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Replace the current child with the requested external command.
 * @param path Resolved executable path returned by path lookup.
 * @param node Simple-command AST node containing argv.
 * @param state Active shell state used for envp and the `_` variable.
 * @return This function does not return. It exits with shell semantics.
 */
static void	child_execution(char *path, t_ast *node, t_shell_state *state)
{
	struct stat	st;

	signal(SIGQUIT, SIG_DFL);
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
 * @brief Fork and wait for one external command execution.
 * @param path Resolved executable path to run in the child.
 * @param node Simple-command AST node containing argv.
 * @param state Active shell state used during execution.
 * @return Normalized wait status for the external command.
 */
static int	run_external_command(char *path, t_ast *node, t_shell_state *state)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_execution(path, node, state);
	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	free(path);
	return (handle_wait_status(status));
}

/**
 * @brief Execute one simple-command AST node.
 * @param node AST node containing the command name and argument vector.
 * @param state Active shell state used for builtin and external execution.
 * @return Command exit status following shell conventions.
 */
int	exec_simple_command(t_ast *node, t_shell_state *state)
{
	char	*path;

	if (!node->args || !node->args[0])
		return (0);
	if (is_builtin(node->args[0], node->args))
		return (exec_builtin(node->args, state));
	path = find_path(node->args[0], state);
	if (!path)
	{
		if (ft_strchr(node->args[0], '/'))
			ft_puterror("%s: No such file or directory\n", node->args[0]);
		else
			ft_puterror("%s: command not found\n", node->args[0]);
		return (127);
	}
	return (run_external_command(path, node, state));
}
