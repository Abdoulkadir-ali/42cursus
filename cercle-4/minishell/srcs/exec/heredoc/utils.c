/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:48:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 04:27:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*prepare_stop_str(char *delim, t_heredoc *ctx)
{
	int		quoted;
	char	*stop_str;

	quoted = is_quoted_delim(delim);
	if (quoted)
		stop_str = remove_quotes_heredoc(delim);
	else
		stop_str = expand_string(delim, ctx->state->envp,
				ctx->state->exit_code);
	if (!stop_str)
		stop_str = ft_strdup(delim);
	return (stop_str);
}

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

char	*heredoc_read_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	else
		return (heredoc_read_line_non_tty());
}

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

int	process_line_unquoted(char *line, char *stop_str, int fd, t_heredoc *ctx)
{
	char	*expanded_candidate;
	char	*trimmed_expanded;
	size_t	len;

	expanded_candidate = expand_heredoc(line, ctx->state->envp,
			ctx->state->exit_code);
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
