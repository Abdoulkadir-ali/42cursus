/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/14 17:47:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int	exec_redirection(t_ast *node, char ***envp)
{
	int	fd;
	int	save_fd;
	int	target_fd;
	int	status;

	target_fd = STDOUT_FILENO;
	if (node->type == TOKEN_RED_IN || node->type == TOKEN_HEREDOC)
		target_fd = STDIN_FILENO;
	if (node->args[1] && ft_isdigit(node->args[1][0]))
		target_fd = ft_atoi(node->args[1]);
	if (open_redirection_file(node, &fd))
		return (1);
	save_fd = dup(target_fd);
	dup2(fd, target_fd);
	close(fd);
	status = exec_tree(node->left, envp);
	dup2(save_fd, target_fd);
	close(save_fd);
	return (status);
}
