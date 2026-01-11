/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

int	path_is_set(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_simple_command(t_ast *node, char ***envp)
{
	char		*path;
	pid_t		pid;
	int			status;
	struct stat	st;

	if (!node->args || !node->args[0])
		return (0);
	if (is_builtin(node->args[0], node->args))
		return (exec_builtin(node->args, envp));
	path = find_path(node->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		if (path_is_set(*envp))
			ft_putendl_fd(": command not found", 2);
		else
			ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(path, node->args, *envp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		if (errno == ENOENT)
		{
			ft_putendl_fd(": No such file or directory", 2);
			exit(127);
		}
		if (errno == EACCES)
		{
			if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
				ft_putendl_fd(": Is a directory", 2);
			else
				ft_putendl_fd(": Permission denied", 2);
			exit(126);
		}
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	exec_redirection(t_ast *node, char ***envp)
{
	int		fd;
	int		save_fd;
	int		target_fd;
	int		status;

	target_fd = STDOUT_FILENO;
	if (node->type == TOKEN_RED_IN || node->type == TOKEN_HEREDOC)
		target_fd = STDIN_FILENO;
	
	if (node->args[1] && ft_isdigit(node->args[1][0]))
		target_fd = ft_atoi(node->args[1]);
	
	if (node->type == TOKEN_RED_IN)
		fd = open(node->args[0], O_RDONLY);
	else if (node->type == TOKEN_RED_OUT)
		fd = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == TOKEN_APPEND)
		fd = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else 
		fd = open(node->args[0], O_RDONLY);

	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(node->args[0]);
		return (1);
	}
	save_fd = dup(target_fd);
	dup2(fd, target_fd);
	close(fd);
	status = exec_tree(node->left, envp);
	dup2(save_fd, target_fd);
	close(save_fd);
	return (status);
}

int	exec_tree(t_nodes *ast_node, char ***envp)
{
	t_ast	*node;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, envp));
	else if (node->type == TOKEN_WORD)
		return (exec_simple_command(node, envp));
	else if (node->type == TOKEN_RED_IN || node->type == TOKEN_RED_OUT
			|| node->type == TOKEN_APPEND || node->type == TOKEN_HEREDOC)
		return (exec_redirection(node, envp));
	return (0);
}
