/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:32:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	exec_simple_command(t_ast *node, char **envp)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!node->args || !node->args[0])
		return (0);
	path = find_path(node->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, node->args, envp);
		perror("minishell");
		exit(126);
	}
	waitpid(pid, &status, 0);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_tree(t_nodes *ast_node, char ***envp)
{
	t_ast	*node;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	// printf("DEBUG: exec_tree node type: %d\n", node->type);
	if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, envp));
	else if (node->type == TOKEN_WORD)
		return (exec_simple_command(node, *envp));
	return (0);
}
