/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:27:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Process one quoted heredoc line without variable expansion.
 * @param line Raw line read from heredoc input.
 * @param stop_str Fully prepared stop delimiter.
 * @param fd Destination descriptor receiving heredoc content.
 * @return 1 when the delimiter is reached, otherwise 0.
 */
int	process_line_quoted(char *line, char *stop_str, int fd)
{
	char	*trimmed_line;
	size_t	len;

	trimmed_line = ft_strtrim(line, " \t");
	len = ft_strlen(stop_str) + 1;
	if (ft_strncmp(trimmed_line, stop_str, len) == 0)
	{
		free(trimmed_line);
		return (1);
	}
	ft_putendl_fd(line, fd);
	free(trimmed_line);
	return (0);
}

/**
 * @param line Raw line read from heredoc input.
 * @param stop_str Fully prepared stop delimiter.
 * @param fd Destination descriptor receiving heredoc content.
 * @param heredoc Heredoc context carrying shell state and target fd.
 * @return 1 when the delimiter is reached, otherwise 0.
 */
int	process_line_unquoted(char *line, char *stop_str, int fd, t_heredoc *heredoc)
{
	char	*expanded_candidate;
	char	*trimmed_expanded;
	size_t	len;

	expanded_candidate = expand_heredoc(line, heredoc->state->envp,
			heredoc->state->exit_code);
	trimmed_expanded = ft_strtrim(expanded_candidate, " \t");
	len = ft_strlen(stop_str) + 1;
	if (ft_strncmp(trimmed_expanded, stop_str, len) == 0)
	{
		free(expanded_candidate);
		free(trimmed_expanded);
		return (1);
	}
	ft_putendl_fd(expanded_candidate, fd);
	free(expanded_candidate);
	free(trimmed_expanded);
	return (0);
}

/**
 * @brief Consume one tokenizer word that follows a heredoc operator.
 * @param tok Word token holding the delimiter text.
 * @param state Active shell state used for delimiter expansion.
 * @return This function does not return a value.
 */
static void	handle_heredoc_word(t_token *tok, t_shell_state *state)
{
	char	*filename;
	int		fd;
	char	*value;
	char	*delim;

	value = tok->value;
	delim = value;
	if (!tok->quoted)
		delim = expand_delim(value);
	filename = generate_tmp_filename(&fd);
	if (fd != -1)
	{
		read_heredoc_loop(delim, fd, state, tok->quoted);
		close(fd);
		unlink(filename);
	}
	free(filename);
	if (!tok->quoted && delim != value)
		free(delim);
}

/**
 * @brief Inspect one token node and consume the heredoc that follows it.
 * @param tokens Current linked-list node in the token stream.
 * @param state Active shell state passed to heredoc readers.
 * @return This function does not return a value.
 */
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
				handle_heredoc_word(next_tok, state);
		}
	}
}

/**
 * @brief Pre-consume every heredoc found in a token list.
 * @param tokens Token stream produced before AST execution.
 * @param state Active shell state passed to heredoc readers.
 * @return This function does not return a value.
 */
void	consume_heredocs(t_nodes *tokens, t_shell_state *state)
{
	while (tokens)
	{
		process_heredoc(tokens, state);
		tokens = tokens->next;
	}
}
