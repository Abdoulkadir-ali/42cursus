/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:17:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_heredoc_word(t_token *tok, t_shell_state *state)
{
	char	*filename;
	int		fd;
	char	*value;
	char	*delim;

	value = tok->value;
	delim = value;
	if (!tok->quoted)
	{
		delim = expand_heredoc(value, state->envp, state->exit_code);
		if (!delim)
			delim = value;
	}
	filename = generate_tmp_filename(&fd);
	if (fd != -1)
	{
		read_heredoc_loop(delim, fd, state);
		close(fd);
		unlink(filename);
	}
	free(filename);
	if (!tok->quoted && delim != value)
		free(delim);
}

static void	process_heredoc(t_nodes *tokens, t_shell_state *state)
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
				handle_heredoc_word(next_tok, state);
			}
		}
	}
}

void	consume_heredocs(t_nodes *tokens, t_shell_state *state)
{
	while (tokens)
	{
		process_heredoc(tokens, state);
		tokens = tokens->next;
	}
}
