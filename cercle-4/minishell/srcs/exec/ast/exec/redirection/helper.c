/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 05:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 12:33:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Validate if a string represents a valid file descriptor number.
 * @param str String containing the candidate FD number.
 * @return 1 if valid and within bounds, otherwise 0.
 */
int	is_valid_fd(const char *str)
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
 * @brief Open a file for redirection based on the AST node type.
 * @param node AST node describing the redirection type and target file.
 * @param fd Pointer to store the resulting file descriptor.
 * @return 0 on success, or 1 on error
 * (e.g. failure to open or directory mismatch).
 */
int	open_redirection_file(t_ast *node, int *fd)
{
	struct stat	target_st;

	if (node->args[0] && stat(node->args[0], &target_st) == 0
		&& S_ISDIR(target_st.st_mode))
	{
		ft_puterror("%s: Is a directory\n", node->args[0]);
		return (1);
	}
	if (cmp_ast_type(node, TOKEN_RED_IN))
		*fd = open(node->args[0], O_RDONLY);
	else if (cmp_ast_type(node, TOKEN_RED_OUT))
		*fd = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmp_ast_type(node, TOKEN_APPEND))
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
 * @brief Resolve the shell's target file descriptor for a redirection node.
 * @param node AST node describing the redirection.
 * @return The target file descriptor number, typically 0 or 1.
 */
int	get_target_fd(t_ast *node)
{
	int	target_fd;

	target_fd = STDOUT_FILENO;
	if (cmp_ast_type(node, TOKEN_RED_IN) || cmp_ast_type(node, TOKEN_HEREDOC))
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
 * @brief Duplicate and replace a target file descriptor with a new one.
 * @param target_fd Original file descriptor (e.g. STDOUT_FILENO).
 * @param fd New file descriptor to swap in.
 * @param save_fd Pointer to store the copy of the original descriptor.
 * @return 0 on success, or 1 on failure.
 */
int	setup_redirection(int target_fd, int fd, int *save_fd)
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
		ft_puterror("%d: Bad file descriptor\n", target_fd);
		return (1);
	}
	close(fd);
	return (0);
}
