/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 05:16:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:23:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Expand and validate a redirection filename, checking for ambiguity.
 * @param node AST node whose redirection target needs expansion.
 * @param state Active shell state used for environment resolution.
 * @return Array of matches or NULL on ambiguity or allocation failure.
 */
static char	**expand_and_validate_filename(t_ast *node, t_shell_state *state)
{
	char	**exp_args;

	exp_args = expand_redirection_filename(node->args[0], state);
	if (!exp_args || !exp_args[0] || exp_args[1])
	{
		ft_puterror("%s: ambiguous redirect\n", node->args[0]);
		free_string_array(exp_args);
		return (NULL);
	}
	return (exp_args);
}

/**
 * @brief Open a descriptor for an expanded redirection target.
 * @param node AST node indicating redirection semantics.
 * @param exp_args Result of filename expansion.
 * @param out_fd Pointer to store the opened file descriptor.
 * @return 0 on success, or 1 on failure.
 */
static int	open_expanded_filename(t_ast *node, char **exp_args, int *out_fd)
{
	char	*real_filename;
	int		fd;

	real_filename = node->args[0];
	node->args[0] = exp_args[0];
	if (open_redirection_file(node, &fd))
	{
		node->args[0] = real_filename;
		free_string_array(exp_args);
		return (1);
	}
	node->args[0] = real_filename;
	free_string_array(exp_args);
	*out_fd = fd;
	return (0);
}

/**
 * @brief Apply the redirection, execute the branch, and restore the descriptor.
 * @param node Redirection node whose branch should be executed.
 * @param target_fd File descriptor to be replaced (e.g. STDOUT).
 * @param fd File descriptor to use for substitution.
 * @param state Active shell state passed recursively.
 * @return Exit status of the executed command subtree.
 */
static int	perform_redirection_and_exec(t_ast *node, int target_fd, int fd,
		t_shell_state *state)
{
	int	save_fd;
	int	status;

	if (setup_redirection(target_fd, fd, &save_fd))
		return (1);
	status = exec_tree(node->left, state);
	dup2(save_fd, target_fd);
	close(save_fd);
	return (status);
}

/**
 * @brief Top-level redirection executor for the AST.
 * @param node Redirection AST node.
 * @param state Active shell state.
 * @return Final exit status of the redirection's command.
 */
int	exec_redirection(t_ast *node, t_shell_state *state)
{
	int		target_fd;
	int		fd;
	char	**exp_args;

	target_fd = get_target_fd(node);
	if (target_fd == -1)
		return (1);
	exp_args = expand_and_validate_filename(node, state);
	if (!exp_args)
		return (1);
	if (open_expanded_filename(node, exp_args, &fd))
		return (1);
	return (perform_redirection_and_exec(node, target_fd, fd, state));
}
