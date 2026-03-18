/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:54 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:16:55 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
	* Unquoted delimiters should undergo variable expansion similar to
	heredoc content. Use the provided shell state's envp as the source.
*/
char	*expand_delim(const char *delim, t_shell_state *state)
{
	if (is_quoted_delim(delim))
		return (remove_quotes_heredoc((char *)delim));
	return (expand_heredoc((char *)delim, state->envp, state->exit_code));
}

/**
 * @brief Read one heredoc line when stdin is not attached to a tty.
 * @return Newly allocated line without the trailing newline, or NULL on EOF.
 */
char	*heredoc_read_line_non_tty(void)
{
	char	*line;
	size_t	len;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

/**
 * @brief Read one heredoc line from either readline or raw stdin.
 * @return Newly allocated input line, or NULL on EOF.
 */
char	*heredoc_read_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	else
		return (heredoc_read_line_non_tty());
}
