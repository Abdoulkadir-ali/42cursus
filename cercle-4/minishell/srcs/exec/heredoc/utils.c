/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:48:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 13:53:20 by abdoali          ###   ########.fr       */
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
		stop_str = expand_string(delim, ctx->envp, ctx->exit_code);
	if (!stop_str)
		stop_str = ft_strdup(delim);
	return (stop_str);
}

char	*read_line_non_tty(void)
{
	char	*buf;
	int		i;
	char	c;

	buf = ft_calloc(10000, 1);
	i = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		buf[i++] = c;
		if (c == '\n')
			break ;
		if (i >= 9999)
			break ;
	}
	if (i > 0)
	{
		if (buf[i - 1] == '\n')
			buf[i - 1] = '\0';
		return (buf);
	}
	else
	{
		free(buf);
		return (NULL);
	}
}

char	*read_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	else
		return (read_line_non_tty());
}

int	process_line_quoted(char *line, char *stop_str, int fd)
{
	size_t	len;

	len = ft_strlen(stop_str) + 1;
	if (ft_strncmp(line, stop_str, len) == 0)
		return (1);
	ft_putendl_fd(line, fd);
	return (0);
}

int	process_line_unquoted(char *line, char *stop_str, int fd,
		t_heredoc *ctx)
{
	char	*expanded_candidate;
	size_t	len;

	expanded_candidate = expand_heredoc(line, ctx->envp, ctx->exit_code);
	len = ft_strlen(stop_str) + 1;
	if (ft_strncmp(expanded_candidate, stop_str, len) == 0)
	{
		free(expanded_candidate);
		return (1);
	}
	ft_putendl_fd(expanded_candidate, fd);
	free(expanded_candidate);
	return (0);
}
