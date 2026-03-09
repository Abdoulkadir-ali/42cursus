/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:20:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Validate a textual file descriptor used by a redirection node.
 * @param str Candidate descriptor string from the parsed AST arguments.
 * @return 1 when the string is a valid non-negative descriptor, else 0.
 */
static int	is_valid_fd(const char *str)
{
	char	*endptr;
	long	val;

	if (!str || !*str)
		return (0);
	val = strtol(str, &endptr, 10);
	if (*endptr || val < 0 || val > INT_MAX)
		return (0);
	return (1);
}

/**
 * @brief Open the file targeted by a redirection AST node.
 * @param node Redirection node containing the filename and token type.
 * @param fd Output slot receiving the opened descriptor on success.
 * @return 0 on success, 1 when the target cannot be opened.
 */
static int	open_redirection_file(t_ast *node, int *fd)
{
	struct stat	target_st;

	if (node->args[0] && stat(node->args[0], &target_st) == 0
		&& S_ISDIR(target_st.st_mode))
	{
		ft_puterror("%s: Is a directory\n", node->args[0]);
		return (1);
	}
	if (node->type == TOKEN_RED_IN)
		*fd = open(node->args[0], O_RDONLY);
	else if (node->type == TOKEN_RED_OUT)
		*fd = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == TOKEN_APPEND)
		*fd = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = open(node->args[0], O_RDONLY);
	if (*fd == -1)
	{
		ft_puterror("%s: ", node->args[0]);
		perror(NULL);
		return (1);
	}
	return (0);
}

/**
 * @brief Select the descriptor replaced by a redirection node.
 * @param node Redirection AST node containing optional explicit fd text.
 * @return Target descriptor, or -1 when the explicit fd is invalid.
 */
static int	get_target_fd(t_ast *node)
{
	int	target_fd;

	target_fd = STDOUT_FILENO;
	if (node->type == TOKEN_RED_IN || node->type == TOKEN_HEREDOC)
		target_fd = STDIN_FILENO;
	if (node->args[1] && ft_isdigit(node->args[1][0]))
	{
		if (!is_valid_fd(node->args[1]))
			return (-1);
		target_fd = ft_atoi(node->args[1]);
	}
	return (target_fd);
}

/**
 * @brief Install an opened redirection descriptor onto its target fd.
 * @param target_fd Descriptor that must be replaced for command execution.
 * @param fd Open file descriptor backing the redirection.
 * @param save_fd Output slot receiving the saved original descriptor.
 * @return 0 on success, 1 when dup or dup2 fails.
 */
static int	setup_redirection(int target_fd, int fd, int *save_fd)
{
	*save_fd = dup(target_fd);
	if (*save_fd == -1)
	{
		close(fd);
		return (1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		close(fd);
		close(*save_fd);
		ft_puterror("minishell: %d: Bad file descriptor\n", target_fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Execute the command wrapped by a single redirection AST node.
 * @param node Redirection node whose left branch is the wrapped command.
 * @param state Active shell state passed to recursive execution.
 * @return Exit status of the wrapped command, or 1 on redirection failure.
 */
int	exec_redirection(t_ast *node, t_shell_state *state)
{
	int	fd;
	int	save_fd;
	int	target_fd;
	int	status;

	target_fd = get_target_fd(node);
	if (target_fd == -1)
		return (1);
	if (open_redirection_file(node, &fd))
		return (1);
	if (setup_redirection(target_fd, fd, &save_fd))
		return (1);
	status = exec_tree(node->left, state);
	dup2(save_fd, target_fd);
	close(save_fd);
	return (status);
}
