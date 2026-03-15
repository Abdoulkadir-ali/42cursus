/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/15 07:35:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Run the interactive heredoc read loop for one delimiter.
 * @param delim Raw delimiter string attached to the heredoc.
 * @param fd Destination descriptor receiving the heredoc body.
 * @param state Active shell state passed to expansion helpers.
 * @param is_quoted True when the delimiter disables line expansion.
 * @return This function does not return a value.
 */
void	read_heredoc_loop(char *delim, int fd, t_shell_state *state,
		bool is_quoted)
{
	char		*stop_str;
	t_heredoc	heredoc;

	heredoc.state = state;
	heredoc.fd = fd;
	if (is_quoted_delim(delim))
		stop_str = remove_quotes_heredoc(delim);
	else
		stop_str = ft_strdup(delim);
	if (!is_quoted)
		is_quoted = is_quoted_delim(delim);
	setup_signals(SIGNAL_HEREDOC);
	read_heredoc_lines(stop_str, is_quoted, &heredoc);
	setup_signals(SIGNAL_INTERACTIVE);
	free(stop_str);
}

/**
 * @brief Report an unexpected EOF while reading a heredoc.
 * @param stop_str Prepared stop string that was expected.
 * @return This function does not return a value.
 */
void	handle_heredoc_eof(char *stop_str)
{
	const char	*error;

	error = "warning: here-document delimited by end-of-file";
	if (stop_str && g_last_signal != 130)
		ft_puterror("%s (wanted `%s')\n", error, stop_str);
}

/**
 * @brief Route one heredoc line through quoted or unquoted processing.
 * @param line Raw line read from the user or stdin.
 * @param stop_str Prepared stop string.
 * @param quoted True when delimiter quoting disables expansion.
 * @param heredoc Heredoc context carrying shell state and output fd.
 * @return 1 when reading must stop, otherwise 0.
 */
static int	process_heredoc_line(char *line, char *stop_str, bool quoted,
		t_heredoc *heredoc)
{
	if (quoted)
		return (process_line_quoted(line, stop_str, heredoc->fd));
	else
		return (process_line_unquoted(line, stop_str, heredoc->fd, heredoc));
}

/**
 * @brief Read heredoc lines until EOF, signal, or delimiter match.
 * @param stop_str Prepared stop string.
 * @param quoted True when delimiter quoting disables expansion.
 * @param heredoc Heredoc context carrying shell state and output fd.
 * @return This function does not return a value.
 */
void	read_heredoc_lines(char *stop_str, bool quoted, t_heredoc *heredoc)
{
	char	*line;

	while (1)
	{
		line = heredoc_read_line();
		if (!line)
		{
			handle_heredoc_eof(stop_str);
			break ;
		}
		if (process_heredoc_line(line, stop_str, quoted, heredoc))
		{
			free(line);
			break ;
		}
		free(line);
	}
}
