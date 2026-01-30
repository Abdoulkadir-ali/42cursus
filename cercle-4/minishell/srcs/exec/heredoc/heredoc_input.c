/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:31:02 by abdoali          ###   ########.fr       */
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
	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

char	*handle_heredoc_input(char **args, t_shell_state *state)
{
	char	*filename;
	int		fd;
	char	*delim;
	int		quoted;
	char	*use_delim;

	delim = args[0];
	quoted = args[1] ? ft_atoi(args[1]) : 0;
	use_delim = delim;
	if (!quoted)
	{
		use_delim = expand_heredoc(delim, state->envp, state->exit_code);
		if (!use_delim)
			use_delim = delim;
	}
	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc tmp");
		free(filename);
		if (!quoted && use_delim != delim)
			free(use_delim);
		return (NULL);
	}
	read_heredoc_loop(use_delim, fd, state);
	close(fd);
	if (!quoted && use_delim != delim)
		free(use_delim);
	if (g_last_signal == 130)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}
