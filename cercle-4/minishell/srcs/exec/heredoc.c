/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 17:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*generate_tmp_filename(void)
{
	static int	i;
	char		*num;
	char		*name;

	num = ft_itoa(i++);
	name = ft_strjoin("/tmp/.minishell_heredoc_", num);
	free(num);
	return (name);
}

static void	read_heredoc_loop(char *delim, int fd)
{
	char	*line;

	setup_signals(SIGNAL_HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_last_signal != 130)
				ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	setup_signals(SIGNAL_INTERACTIVE);
}

static char	*handle_heredoc_input(char *delim)
{
	char	*filename;
	int		fd;

	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc tmp");
		free(filename);
		return (NULL);
	}
	read_heredoc_loop(delim, fd);
	close(fd);
	if (g_last_signal == 130)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}

int	scan_heredocs(t_nodes *ast_node)
{
	t_ast	*node;
	char	*tmp_file;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_HEREDOC)
	{
		tmp_file = handle_heredoc_input(node->args[0]);
		if (!tmp_file)
			return (1);
		free(node->args[0]);
		node->args[0] = tmp_file;
		node->type = TOKEN_RED_IN;
	}
	if (scan_heredocs(node->left) || scan_heredocs(node->right))
		return (1);
	return (0);
}
