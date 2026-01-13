/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:22:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	scan_heredocs(t_nodes *ast_node)
{
	t_ast	*node;
	char	*tmp_file;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_HEREDOC)
	{
		tmp_file = handle_heredoc_input(node->args[0], g_envp, g_exit_code);
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

static void	handle_heredoc_word(char *value)
{
	char	*filename;
	int		fd;

	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		read_heredoc_loop(value, fd, g_envp, g_exit_code);
		close(fd);
		unlink(filename);
	}
	free(filename);
}

static void	process_heredoc(t_nodes *tokens)
{
	t_token	*tok;
	t_token	*next_tok;

	tok = (t_token *)tokens->content;
	if (tok->type == TOKEN_HEREDOC)
	{
		if (tokens->next)
		{
			next_tok = (t_token *)tokens->next->content;
			if (next_tok->type == TOKEN_WORD)
			{
				handle_heredoc_word(next_tok->value);
			}
		}
	}
}

void	consume_heredocs(t_nodes *tokens)
{
	while (tokens)
	{
		process_heredoc(tokens);
		tokens = tokens->next;
	}
}

char	*handle_heredoc_input(char *delim, char **envp, int exit_code)
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
	read_heredoc_loop(delim, fd, envp, exit_code);
	close(fd);
	if (g_last_signal == 130)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}
