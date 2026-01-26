/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:32:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_heredoc_word(char *value)
{
	char	*filename;
	int		fd;

	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		read_heredoc_loop(value, fd, g_state.envp, g_state.exit_code);
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
	if (g_state.last_signal == 130)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}
